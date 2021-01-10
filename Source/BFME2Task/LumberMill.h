// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IconWidget.h"
#include "UIComponent.h"
#include "Worker.h"
#include "GameFramework/Actor.h"
#include "LumberMill.generated.h"


UCLASS()
class BFME2TASK_API ALumberMill : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALumberMill();

private:
	UFUNCTION()
	void SpawnWorker(UPrimitiveComponent* Component, FKey Key);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UIconWidget> IconWidget;

	UPROPERTY(EditAnywhere)
	UIconWidget* Icon;

	UPROPERTY(VisibleAnywhere)
	UUIComponent* UIComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PlaneComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWorker> ObjectToSpawn;
};
