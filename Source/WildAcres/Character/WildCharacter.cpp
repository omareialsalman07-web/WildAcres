// Fill out your copyright notice in the Description page of Project Settings.


#include "WildCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AWildCharacter::AWildCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());

	Camera->SetRelativeLocation(FVector(0.f, 0.f, 64.f));
	Camera->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = true;
}

// Called when the game starts or when spawned
void AWildCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWildCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWildCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AWildCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWildCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AWildCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AWildCharacter::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AWildCharacter::Jump);
}

void AWildCharacter::MoveForward(float Value)
{
	if (Value != 0.f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AWildCharacter::MoveRight(float Value)
{
	if (Value != 0.f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AWildCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AWildCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}