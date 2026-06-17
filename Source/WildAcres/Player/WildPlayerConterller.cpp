// Fill out your copyright notice in the Description page of Project Settings.


#include "WildPlayerConterller.h"
#include "../UI/WildHUD.h"

void AWildPlayerConterller::BeginPlay()
{
	Super::BeginPlay();

	WildHud = Cast<AWildHUD>(GetHUD());
}

void AWildPlayerConterller::ShowInteractionText(const FText& text)
{
	if (WildHud)
	{
		WildHud->ShowInteractionText(text);
	}
}
