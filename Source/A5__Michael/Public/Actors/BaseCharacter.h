// Fill out your copyright notice in the Description page of Project Settings.

// Includes
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Actors/Rifle.h"
#include "../Both/CharacterAnimation.h"
#include "Actors/Projectile.h"
#include "Utilities/HealthComponent.h"
#include "Both/PlayerHUD.h"
// Final Inlcude
#include "BaseCharacter.generated.h"

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterDeath);

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
	UFUNCTION() void OnReloadEndHandler();
	UFUNCTION() void OnReloadNowHandler();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") class UHealthComponent* HealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Events") FOnCharacterDeath onCharacterDeath;

	UFUNCTION() void HandleDeath(float Ratio);
	UFUNCTION() void HandleHurt(float Ratio);
	void DelayedDestruction();
	FTimerHandle TimerHandleDestroy;

	UFUNCTION() void FireAnimation();
	UFUNCTION() void HurtAnimation(AActor* OtherActor);
	UFUNCTION() void HandleRifleFire(AActor* OtherActor);
	UFUNCTION() void OnReloadStartHandler();
};
