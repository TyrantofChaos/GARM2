// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

UCLASS()
class A5__MICHAEL_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Pickup Action
	UFUNCTION() virtual void HandleOverlap(UPrimitiveComponent* OverLappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") class UParticleSystemComponent* PickupEffect;

	UFUNCTION() bool CanPickup(AActor* OtherActor);

	virtual void HandlePickup(AActor* OtherActor, const FHitResult SweepResult);
	virtual void HandlePostPickup();

};
