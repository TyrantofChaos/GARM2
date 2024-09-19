// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BasePickup.h"
#include "FirePickup.generated.h"

/**
 * 
 */
UCLASS()
class A5__MICHAEL_API AFirePickup : public ABasePickup
{
	GENERATED_BODY()
public:

	AFirePickup();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void HandlePickup(AActor* OtherActor, const FHitResult SweepResult) override;
	virtual void HandlePostPickup() override;

	UPROPERTY(EditAnywhere, Category = "Damage") float DamageAmount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variable) TSubclassOf<class UDamageType> DamageType;
	
};
