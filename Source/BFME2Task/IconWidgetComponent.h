// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "IconWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class BFME2TASK_API UIconWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere)
	UUserWidget* Icon;
};
