// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rifle.generated.h"

UCLASS()
class A5__MICHAEL_API ARifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARifle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Attack();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default) class USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variable) TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variable) APawn* ParentPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) FVector gunOffSet;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) class USceneComponent* MuzzleLoc;
	FRotator spawnRotation;
	FVector spawnLocation;
};
