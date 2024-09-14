// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class A5__MICHAEL_API AProjectile : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USphereComponent* SphereCollision;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UStaticMeshComponent* SphereMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Projectile) class UProjectileMovementComponent* projectileMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variable) AController* OwnerController;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variable) float DamageAmount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variable) FVector Size;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float sphereRadius;

	void FireInDirection(const FVector& ShootDirection);

private:
	UFUNCTION()
	void BindToHitFunction(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION() void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& hit);
};
