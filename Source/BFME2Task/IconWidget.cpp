// Fill out your copyright notice in the Description page of Project Settings.


#include "IconWidget.h"

bool UIconWidget::Initialize()
{
	Icon = CreateWidget(this, IconClass);
	if (Icon != nullptr)
		Icon->AddToViewport();
	return true;
}
