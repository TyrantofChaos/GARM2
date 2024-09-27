// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BasePickup.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class A5__MICHAEL_API AAmmoPickup : public ABasePickup
{
	GENERATED_BODY()
	
public:

	AAmmoPickup();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:

	virtual void HandlePickup(AActor* OtherActor, const FHitResult SweepResult) override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:

	UPROPERTY(VisibleAnywhere, Category = "Components") UStaticMeshComponent* AmmoMesh;
};
