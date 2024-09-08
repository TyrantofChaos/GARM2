// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Actors/Rifle.h"
#include "../Both/CharacterAnimation.h"
#include "BaseCharacter.generated.h"

UCLASS()
class A5__MICHAEL_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = defualt) class UChildActorComponent* childActor;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) class USkeletalMeshComponent* skeleton;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile) TSubclassOf<class AProjectile> projectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation") class UCharacterAnimation* characterAnimation;
	UWorld* world;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon) TSubclassOf<AActor> WeaponClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon) class ARifle* rifle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) FVector gunOffSet;

	FRotator spawnRotation;
	FVector spawnLocation;

	void OnFire();

};
