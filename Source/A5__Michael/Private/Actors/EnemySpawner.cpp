// Fill out your copyright notice in the Description page of Project Settings.


#include "../A5__Michael.h"
#include "../A5__MichaelGameModeBase.h"
#include "Actors/EnemySpawner.h"
// Components
#include "Components/BoxComponent.h"
// Kismet
#include <Kismet/GameplayStatics.h>

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	SpawnRate = 3.f;
	bIsSpawning = false;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnEnemy();
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnEnemy, SpawnRate, true);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AEnemySpawner::SpawnEnemy()
{
	if (EnemyClass)
	{
		FVector Center = BoxCollision->GetComponentLocation();
		FVector Extents = BoxCollision->GetScaledBoxExtent();

		// Create Bounding Box
		FBox SpawnBox(Center - Extents, Center + Extents);

		// Get random Location withing Spawn Area
		FVector SpawnLocation = FMath::RandPointInBox(SpawnBox);

		// Log the spawn location
		UE_LOG(SpawnLog, Log, TEXT("Spawn Location %s"), *SpawnLocation.ToString());
		AEnemy* neuEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
		
		if (neuEnemy)
		{
			AA5__MichaelGameModeBase* gameMode = Cast< AA5__MichaelGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			if (gameMode) gameMode->AddEnemy(Cast<AActor>(neuEnemy));			
		}

	}
	else UE_LOG(SpawnLog, Error, TEXT("Enemy class is not set in spawner"));
}

void AEnemySpawner::TakeDamage(float DamageAmount)
{
	CurrentHealth -= DamageAmount;

	if (CurrentHealth <= 0) DestroySpawner();
	
}

void AEnemySpawner::StartSpawning()
{
	if (!bIsSpawning)
	{
		bIsSpawning = true;
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnTimerElapsed, SpawnRate, true);
	}
}

void AEnemySpawner::StopSpawning()
{
	if (bIsSpawning)
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		bIsSpawning = false;
	}
}

void AEnemySpawner::SpawnTimerElapsed()
{
	SpawnEnemy();
}

void AEnemySpawner::OnSpawnerHit(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& SweepResult)
{
	if (Other->IsA(AProjectile::StaticClass()))
	{
		TakeDamage(10.f);
		UE_LOG(SpawnLog, Error, TEXT("Enemy class is not set in the spawner"));
	}
}

void AEnemySpawner::DestroySpawner()
{
	Destroy();
}