// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/HealthPickup.h"
#include "Actors/BasePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Utilities/HealthComponent.h"

AHealthPickup::AHealthPickup()
{
	HealAmount = -2.f;
}

void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();
}

void AHealthPickup::HandlePickup(AActor* OtherActor, const FHitResult SweepResult)
{
	ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor);
	if (Character && Character->HealthComponent)
	{
		UGameplayStatics::ApplyDamage(OtherActor, HealAmount, nullptr, this, DamageType);
		HandlePostPickup();
	}
}

void AHealthPickup::HandlePostPickup()
{
	Destroy();
}
