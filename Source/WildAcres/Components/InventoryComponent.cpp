#include "InventoryComponent.h"
#include "../Character/WildCharacter.h"
#include "../Interfaces/UsableObject.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	WildCharacter = Cast<AWildCharacter>(GetOwner());

	BindUseEvent();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInventoryComponent::AddItem(AActor* Item)
{
	if (!Item || !WildCharacter || isFull()) return;

	Item->AttachToComponent(WildCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "HandGrip_R");

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

void UInventoryComponent::UseCurrentItem()
{
	if (!CurrentItem) return;
	if (!CurrentItem->Implements<UUsableObject>()) return;

	IUsableObject* UsableObject = Cast<IUsableObject>(CurrentItem);
	if (!UsableObject) return;

	UsableObject->StartUse(GetOwner());
}

bool UInventoryComponent::isFull()
{
	return CurrentItem != nullptr;
}

void UInventoryComponent::BindUseEvent()
{
	if (WildCharacter)
	{
		WildCharacter->OnUseAnimEvent.AddUObject(this, &ThisClass::ExecuteCurrentItem);
	}
}

void UInventoryComponent::ExecuteCurrentItem()
{
	IUsableObject* UsableObject = Cast<IUsableObject>(CurrentItem);
	if (!UsableObject) return;

	UsableObject->ExecuteUse(GetOwner());
}