// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IconWidget.h"
#include "Components/WidgetComponent.h"
#include "UIComponent.generated.h"

/**
 * 
 */
UCLASS()
class BFME2TASK_API UUIComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:

	void AddUIToViewport();
	UPROPERTY(EditAnywhere)
	UUserWidget* Icon;
};
