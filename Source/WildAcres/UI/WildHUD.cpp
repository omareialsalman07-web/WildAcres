// Fill out your copyright notice in the Description page of Project Settings.


#include "WildHUD.h"
#include "Widgets/InteractionWidget.h"

void AWildHUD::BeginPlay()
{
	Super::BeginPlay();

	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
	}
	InteractionWidget->AddToViewport();
}

void AWildHUD::ShowInteractionText(const FText& message)
{
	if (InteractionWidget)
	{
		InteractionWidget->Set_InteractionText(message);
	}
}
