// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/NotifyReloadEnd.h"
#include <Actors/BaseCharacter.h>

void UNotifyReloadEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if (Character)
		{
			Character->OnReloadEndHandler();
		}
	}
}
