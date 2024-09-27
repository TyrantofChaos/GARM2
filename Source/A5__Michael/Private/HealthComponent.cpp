// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	maxHealth = 5.f;
	currentHealth = 0.f;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	currentHealth = maxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleDamage);
	
}

void UHealthComponent::HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser)
{
	currentHealth -= Damage;
	if (currentHealth > 0.f)
	{
		if (Damage > 0)
		{
			onHurt.Broadcast(currentHealth / maxHealth);
		}
		else
		{
			onHeal.Broadcast(0.f);
		}
	}
	else
	{
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::HandleDamage);
		onDead.Broadcast(0.f);
	}
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

