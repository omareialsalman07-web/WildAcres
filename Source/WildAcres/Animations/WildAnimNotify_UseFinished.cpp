// Fill out your copyright notice in the Description page of Project Settings.


#include "WildAnimNotify_UseFinished.h"
#include "../Character/WildCharacter.h"

void UWildAnimNotify_UseFinished::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AWildCharacter* WildCharacter = Cast<AWildCharacter>(MeshComp->GetOwner());

	if (WildCharacter)
	{
		WildCharacter->OnUseAnimEvent.Broadcast();
	}
}
