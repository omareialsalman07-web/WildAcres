#include "InventoryComponent.h"
#include "../Character/WildCharacter.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;


}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	WildCharacter = Cast<AWildCharacter>(GetOwner());
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInventoryComponent::AddItem(AActor* Item)
{
	if (!Item || !WildCharacter || isFull()) return;

	Item->AttachToComponent(WildCharacter->GetHoldPoint(),FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	Item->SetActorEnableCollision(false);

	CurrentItem = Item;
}

void UInventoryComponent::DropItem(AActor* item)
{
	if (!CurrentItem || !WildCharacter) return;
	
	item->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	// Place in front of player
	FVector Forward = WildCharacter->GetActorForwardVector();
	FVector DropLocation = WildCharacter->GetActorLocation() + Forward * 100.f;

	item->SetActorLocation(DropLocation);

	// Re-enable interaction
	item->SetActorEnableCollision(true);

	CurrentItem = nullptr;
}

bool UInventoryComponent::isFull()
{
	return CurrentItem != nullptr;
}
