// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CharacterAnimation.h"
#include "KismetAnimationLibrary.h"

void UCharacterAnimation::NativeUpdateAnimation(float DeltaSeconds) {
	APawn *Pawn = TryGetPawnOwner();
	if(Pawn) 
	{
		{
			//Is Valid
			Velocity = Pawn->GetVelocity().Size();

			Direction = UKismetAnimationLibrary::CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
		}
	} 
	else 
	{
		// Is Not Valid
		PreviewWindowUpdate();
	}
}

void UCharacterAnimation::PreviewWindowUpdate_Implementation() 
{
	if (DebugFire)
	{
		DebugFire = false;
		FireAnimation();
	}
	if (DebugHurt)
	{
		DebugHurt = false;
		HurtAnimation(0.f);
	}
	if (DebugDead)
	{
		DebugDead = false;
		DeathAnimation(0.f);
	}
	if (DebugReload)
	{
		DebugReload = false;
		ReloadAnimation();
	}
}

void UCharacterAnimation::FireAnimation()
{
	PlaySlotAnimationAsDynamicMontage(FireAsset, FName("Action"));
}

void UCharacterAnimation::HurtAnimation(float Unused)
{
	PlaySlotAnimationAsDynamicMontage(HurtAsset, FName("Action"));
}

void UCharacterAnimation::DeathAnimation(float Unused)
{
	DeathAnimation_Implementation();
}

void UCharacterAnimation::DeathAnimation_Implementation()
{
	if (DeadAssets.Num() > 0)
	{
		int32 randomIndex = FMath::RandRange(0, DeadAssets.Num() - 1);
		DeadAsset = DeadAssets[randomIndex];
	}
	PlaySlotAnimationAsDynamicMontage(DeadAsset, FName("Action"));
}

void UCharacterAnimation::ReloadAnimation()
{
	PlaySlotAnimationAsDynamicMontage(ReloadAsset, FName("Action"));
}

void UCharacterAnimation::AnimNotify_BP_ReloadEnd()
{
	onReloadEnded.Broadcast();
}

void UCharacterAnimation::AnimNotify_BP_ReloadNow()
{
	onReloadNow.Broadcast();
}
