// Copyright Epic Games, Inc. All Rights Reserved.

#include "BFME2TaskPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "BFME2TaskCharacter.h"
#include "DrawDebugHelpers.h"
#include "LumberMill.h"
#include "Engine/World.h"

ABFME2TaskPlayerController::ABFME2TaskPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	PlayerController = this;
	bEnableClickEvents = true;
}

void ABFME2TaskPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();

		FHitResult HitResult;
		if (GetHitResultUnderCursor(ECC_Camera, true, HitResult))
		{
			if (PlayerController != nullptr)
			{
				FVector MouseLocation, MouseDirection;
				PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
				float TraceLength = 1000.f;
				FVector EndTraceLocation =  (MouseLocation -  PlayerController->PlayerCameraManager->GetCameraLocation()) * TraceLength;

				// DrawDebugLine(GetWorld(), MouseLocation, EndTraceLocation, FColor{ 255,0,0 }, true, 100, 0, 1);
				if (GetWorld()->LineTraceSingleByChannel(HitResult,MouseLocation, EndTraceLocation,ECC_Camera))
				{
					UE_LOG(LogTemp,Warning, TEXT("HIT OBJECT NAME: %s"), *HitResult.Actor->GetName());
					if (HitResult.Actor->GetName() == TEXT("BP_LumberMill_8"))
					{
						UE_LOG(LogTemp,Warning, TEXT("HIT CLASS NAME: %s"), *HitResult.GetActor()->GetClass()->GetName());
					}
				}
			}
		}
	}
}

void ABFME2TaskPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this,
	                           &ABFME2TaskPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this,
	                           &ABFME2TaskPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ABFME2TaskPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ABFME2TaskPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ABFME2TaskPlayerController::OnResetVR);
}

void ABFME2TaskPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ABFME2TaskPlayerController::MoveToMouseCursor()
{
	
	// UE_LOG(LogTemp, Warning, TEXT("XDDDDD CYLINDER"));

	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ABFME2TaskCharacter* MyPawn = Cast<ABFME2TaskCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(
					this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ABFME2TaskPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ABFME2TaskPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ABFME2TaskPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ABFME2TaskPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
