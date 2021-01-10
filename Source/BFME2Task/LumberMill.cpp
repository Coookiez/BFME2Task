// Fill out your copyright notice in the Description page of Project Settings.


#include "LumberMill.h"
#include <iostream>

#include "BFME2TaskCharacter.h"

// Sets default values
ALumberMill::ALumberMill()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ALumberMill::SpawnWorker(UPrimitiveComponent*, FKey)
{
	FVector Location(0.0f, 0.0f, 265.588348f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<AWorker>(ObjectToSpawn, Location, Rotation, SpawnInfo);
}

// Called when the game starts or when spawned
void ALumberMill::BeginPlay()
{
	Super::BeginPlay();
	UIComponent = FindComponentByClass<UUIComponent>();

	TArray<UActorComponent*> Meshes = GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (auto x : Meshes)
	{
		if (x->GetName() == "Plane")
		{
			PlaneComponent = Cast<UStaticMeshComponent>(x);
			break;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("plane:  %s"), *PlaneComponent->GetName());

	PlaneComponent->OnClicked.AddDynamic(this,  &ALumberMill::SpawnWorker);

	if (UIComponent != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Nie null"));
		UIComponent->AddUIToViewport();
	}
	
}



// Called every frame
void ALumberMill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
