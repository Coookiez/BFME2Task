// Copyright Epic Games, Inc. All Rights Reserved.

#include "BFME2TaskGameMode.h"
#include "BFME2TaskPlayerController.h"
#include "BFME2TaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABFME2TaskGameMode::ABFME2TaskGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ABFME2TaskPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}