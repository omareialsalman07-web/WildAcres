// Fill out your copyright notice in the Description page of Project Settings.


#include "WildAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void UWildAnimInstance::NativeInitializeAnimation()
{

}

void UWildAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (!Pawn) return;

	FVector Velocity = Pawn->GetVelocity();
	Velocity.Z = 0.f;

	Speed = Velocity.Size();

	Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, Pawn->GetActorRotation());

	if (ACharacter* Character = Cast<ACharacter>(Pawn))
	{
		bIsInAir = Character->GetCharacterMovement()->IsFalling();
	}

	VerticalSpeed = Pawn->GetVelocity().Z;
}