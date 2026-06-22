// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UsableObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUsableObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WILDACRES_API IUsableObject
{
	GENERATED_BODY()

	
public:
	virtual void StartUse(AActor* User) = 0;

	virtual void ExecuteUse(AActor* User) = 0;
};
