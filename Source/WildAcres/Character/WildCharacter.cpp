#include "WildCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "../Components/InteractionComponent.h"
#include "../Components/InventoryComponent.h"

AWildCharacter::AWildCharacter()
{
 	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());

	Camera->SetRelativeLocation(FVector(0.f, 0.f, 64.f));
	Camera->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = true;

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	HoldPoint = CreateDefaultSubobject<USceneComponent>(TEXT("HoldPoint"));
	HoldPoint->SetupAttachment(Camera);

	HoldPoint->SetRelativeLocation(FVector(100.f, 0.f, -20.f));

}

void AWildCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWildCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWildCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AWildCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWildCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AWildCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AWildCharacter::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AWildCharacter::Jump);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AWildCharacter::InteractButton_Pressed);
	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AWildCharacter::DropButton_Pressed);
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

void AWildCharacter::InteractButton_Pressed()
{
	if (!InteractionComponent)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString("Interaction Component is NULL"));
		}
		return;
	}

	InteractionComponent->Interact();
}

void AWildCharacter::DropButton_Pressed()
{
	if (!InventoryComponent)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString("Inventory Component is NULL"));
		}
		return;
	}

	// TEMPORARY : for now as we have one item in the inventory
	InventoryComponent->DropItem(InventoryComponent->GetSelectedItem());
}
