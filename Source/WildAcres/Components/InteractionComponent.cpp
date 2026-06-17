#include "InteractionComponent.h"
#include "Components/SphereComponent.h"
#include "../Pickups/PickupItem.h"
#include "../Character/WildCharacter.h"
#include "InventoryComponent.h"
#include "../Player/WildPlayerConterller.h"


UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));

	SphereCollision->SetSphereRadius(200.f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

}


void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->AttachToComponent(GetOwner()->GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this,&ThisClass::OnOverlapEnd);
	
}

void UInteractionComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString("Overlaped with actor"));
	}

	if (OtherActor && OtherActor->Implements<UInteractableObject>())
	{
		overlappedInteractable = Cast<IInteractableObject>(OtherActor);

	}

	_UpdateInteractionText();
}

void UInteractionComponent::OnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (overlappedInteractable == Cast<IInteractableObject>(OtherActor))
	{
		overlappedInteractable = nullptr;
	}
	_UpdateInteractionText();
}


void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UInteractionComponent::Interact()
{
	if(overlappedInteractable)
		overlappedInteractable->OnInteract(GetOwner());
}

void UInteractionComponent::_UpdateInteractionText()
{
	UWorld* world = GetWorld();
	if (!world) return;

	AWildPlayerConterller* PC = Cast<AWildPlayerConterller>(world->GetFirstPlayerController());
	if (!PC) return;

	AWildCharacter* character = Cast<AWildCharacter>(GetOwner());
	if (!character) return;

	UInventoryComponent* inv = character->GetInventoryComponent();

	if (inv && !inv->isFull())
	{
		if (overlappedInteractable)
			PC->ShowInteractionText(FText::FromString(overlappedInteractable->GetInteractionMessage()));
		else
			PC->ShowInteractionText(FText::FromString(""));
	}
}

