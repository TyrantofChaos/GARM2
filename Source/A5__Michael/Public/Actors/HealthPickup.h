// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BasePickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class A5__MICHAEL_API AHealthPickup : public ABasePickup
{
	GENERATED_BODY()
	
public:

	AHealthPickup();

protected:

	virtual void BeginPlay() override;

public:

	virtual void HandlePickup(AActor* OtherActor, const FHitResult SweepResult) override;

	virtual void HandlePostPickup() override;

private:

	UPROPERTY(EditAnywhere, Category = "Health") float HealAmount;
	UPROPERTY(EditDefaultsOnly, Category = Variable) TSubclassOf<class UDamageType> DamageType;
};
