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

void ALumberMill::SpawnWorker()
{
	FVector MillLocation = GetActorLocation();
	FVector Location(MillLocation.X - 130.f ,MillLocation.Y, 265.588348f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<AWorker>(ObjectToSpawn, Location, Rotation, SpawnInfo);
	WorkerQueue->Dequeue();
	UE_LOG(LogTemp, Warning, TEXT("dequeue # of elements:  %d"), WorkerQueue->Count());
}

void ALumberMill::PlaneOnClick(UPrimitiveComponent*, FKey)
{
	if (PlaneComponent->IsVisible())
	{
		WorkerQueue->Enqueue(NewObject<AWorker>());
		UpdateWorkerQueueCounter();
		UE_LOG(LogTemp, Warning, TEXT("# of elements:  %d"), WorkerQueue->Count());
	}
	// GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ALumberMill::SpawnWorker, 2.f, false);
}

void ALumberMill::UpdateWorkerQueueCounter()
{
	if (WorkersQueueText != nullptr)
	{
		WorkersQueueText->SetText(FText::AsNumber(WorkerQueue->Count()));
		UE_LOG(LogTemp, Warning, TEXT("WorkersQueueText NOT null, count %d"), WorkerQueue->Count());
	}
}

// Called when the game starts or when spawned
void ALumberMill::BeginPlay()
{
	Super::BeginPlay();
	WorkersQueueText = FindComponentByClass<UTextRenderComponent>();
	WorkerQueue = new TCircularQueue<AWorker*>(10);
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

	PlaneComponent->OnClicked.AddDynamic(this, &ALumberMill::PlaneOnClick);
}


// Called every frame
void ALumberMill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (WorkerQueue->Count() != 0)
	{
		if (TimeSinceLastWorkerSpawned >= WorkerSpawnTime)
		{
			SpawnWorker();
			UpdateWorkerQueueCounter();
			TimeSinceLastWorkerSpawned = 0.f;
		}
		TimeSinceLastWorkerSpawned += DeltaTime;
	}
}
