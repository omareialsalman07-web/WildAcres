#include "WildCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "../Components/InteractionComponent.h"
#include "../Components/InventoryComponent.h"

AWildCharacter::AWildCharacter()
{
 	PrimaryActorTick.bCanEverTick = false;

	_CreateComponents();
	_SetupCamera();
	_SetupCharacter();
	_SetupMovment();
}

void AWildCharacter::_CreateComponents()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void AWildCharacter::_SetupCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -100.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, 0.f, -100.0f));

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
}

void AWildCharacter::_SetupCamera()
{
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AWildCharacter::_SetupMovment()
{
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
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
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(ForwardDirection, Value);
	}
}

void AWildCharacter::MoveRight(float Value)
{
	if (Value != 0.f)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(RightDirection, Value);
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
