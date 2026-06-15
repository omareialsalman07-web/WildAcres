// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/InteractableObject.h"
#include "PickupItem.generated.h"

UCLASS()
class WILDACRES_API APickupItem : public AActor, public IInteractableObject
{
	GENERATED_BODY()
	
public:	
	APickupItem();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

public:	
	virtual void Tick(float DeltaTime) override;

	void OnInteract(AActor* interactor) override;

};
