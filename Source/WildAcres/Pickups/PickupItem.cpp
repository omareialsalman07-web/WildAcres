#include "PickupItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "../Character/WildCharacter.h"
#include "../Components/InventoryComponent.h"


APickupItem::APickupItem()
{
 	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

void APickupItem::BeginPlay()
{
	Super::BeginPlay();

}

void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupItem::OnInteract(AActor* interactor)
{
	AWildCharacter* Character = Cast<AWildCharacter>(interactor);
	if (!Character) return;

	UInventoryComponent* inv = Character->GetInventoryComponent();

	if (inv)
	{
		inv->AddItem(this);
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString("Can't get Inventory Component from character : PickupItem.cpp"));
		}
	}
}

FString APickupItem::GetInteractionMessage() const
{
	return FString("[E] To Pickup");
}
