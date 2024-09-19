// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Projectile.h"
#include "GameFramework/Actor.h"
// Final Include
#include "Rifle.generated.h"

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRifleFire);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionStopped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChanged, float, CurrentAmmo, float, MaxAmmo);


UCLASS()
class A5__MICHAEL_API ARifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARifle();

	// Declare Delegates
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events") FOnRifleFire onRifleFire;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events") FOnActionStopped onActionStopped;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events") FOnAmmoChanged onAmmoChanged;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events") FOnReloadStart onReloadStart;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintREadWrite, Category = Variable) bool ActionHappening;
	UPROPERTY(EditDefaultsOnly, BlueprintREadWrite, Category = Variable) float Time;
	UPROPERTY(EditDefaultsOnly, BlueprintREadWrite, Category = Variable) bool OwnerAlive;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Attack();

	UFUNCTION(BlueprintCallable) void OwnerDied();
	UFUNCTION(BlueprintCallable) bool CanShoot() const;
	UFUNCTION(BlueprintCallable) FVector GetShotLocation() const;
	UFUNCTION(BlueprintCallable) void ActionStopped();
	UFUNCTION(BlueprintCallable) void ReloadAmmo();
	UFUNCTION(BlueprintCallable) bool CanReload() const;
	UFUNCTION(BlueprintCallable) void RequestReload();
	UFUNCTION(BlueprintCallable) void UseAmmo();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variable) float MaxAmmo;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variable) float CurrentAmmo;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default) class USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile") TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variable) APawn* ParentPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) FVector gunOffSet;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) class USceneComponent* MuzzleLoc;
	FRotator spawnRotation;
	FVector spawnLocation;
};
