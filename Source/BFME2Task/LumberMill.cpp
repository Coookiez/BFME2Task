// Fill out your copyright notice in the Description page of Project Settings.


#include "LumberMill.h"
#include "IconWidget.h"

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
	IconWidget = NewObject<UIconWidget>();
	IconWidget->Initialize();
	if (IconWidget != nullptr)
		UE_LOG(LogTemp, Warning, TEXT("IconWidget is not null - beginplay") );
}

// Called every frame
void ALumberMill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
