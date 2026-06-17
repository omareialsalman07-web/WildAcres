// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WildHUD.generated.h"

class UInteractionWidget;

UCLASS()
class WILDACRES_API AWildHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;

	UPROPERTY()
	UInteractionWidget* InteractionWidget;

public:
	void ShowInteractionText(const FText& message);
};
