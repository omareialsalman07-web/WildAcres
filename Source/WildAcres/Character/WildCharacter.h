// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WildCharacter.generated.h"

UCLASS()
class WILDACRES_API AWildCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWildCharacter();

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void LookUp(float Value);
	void Turn(float Value);

	// Components
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class UInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere)
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* HoldPoint;

private:
	void InteractButton_Pressed();
	void DropButton_Pressed();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }

	FORCEINLINE USceneComponent* GetHoldPoint() { return HoldPoint; }
};
