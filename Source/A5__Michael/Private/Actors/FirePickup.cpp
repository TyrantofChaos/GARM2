// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FirePickup.h"
#include "Actors/BasePickup.h"
#include "Actors/BaseCharacter.h"
#include "Utilities/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

AFirePickup::AFirePickup()
{
	DamageAmount = 0.5f;
}

void AFirePickup::BeginPlay()
{
	Super::BeginPlay();
}

void AFirePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFirePickup::HandlePickup(AActor* OtherActor, const FHitResult SweepResult)
{
	Super::HandlePickup(OtherActor, SweepResult);
	ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor);
	if (Character && Character->HealthComponent)
	{
		// Apply Damage
		UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, nullptr, this, DamageType);

		// Makes sure to not Destroy this one
		HandlePostPickup();
	}
}

void AFirePickup::HandlePostPickup()
{
	// do nothing
}
