// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/Enemy.h"
// Final Include
#include "EnemySpawner.generated.h"

UCLASS()
class A5__MICHAEL_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") class UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") class UStaticMeshComponent* StaticMesh;

	// Spawn Enemy
	UFUNCTION(BlueprintCallable) void SpawnEnemy();
	// Handle Damage
	void TakeDamage(float DamageAmount);
	// Start Spawning
	UFUNCTION(BlueprintCallable) void StartSpawning();
	// Stop Spawning
	UFUNCTION(BlueprintCallable) void StopSpawning();

private:

	FTimerHandle SpawnTimerHandle;
	UPROPERTY(Editanywhere, Category = "Spawner") TSubclassOf<AEnemy> EnemyClass;
	// Handle Timer Expiration
	void SpawnTimerElapsed();
	// Spawn Rate
	UPROPERTY(EditAnywhere, Category = "Spawner") float SpawnRate;
	bool bIsSpawning;

	UPROPERTY(EditAnywhere) float MaxHealth = 5.f;
	float CurrentHealth;

	UFUNCTION()
	virtual void OnSpawnerHit(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& SweepResult);

	void DestroySpawner();

};
