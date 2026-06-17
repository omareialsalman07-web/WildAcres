// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WildPlayerConterller.generated.h"

/**
 * 
 */
UCLASS()
class WILDACRES_API AWildPlayerConterller : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	class AWildHUD* WildHud;

public:
	void ShowInteractionText(const FText& text);
};
