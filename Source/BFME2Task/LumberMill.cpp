// Fill out your copyright notice in the Description page of Project Settings.


#include "LumberMill.h"

#include <iostream>

// Sets default values
ALumberMill::ALumberMill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALumberMill::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("XDDDDD CYLINDER") );
}

// Called every frame
void ALumberMill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

