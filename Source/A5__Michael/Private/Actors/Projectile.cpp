// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../A5__Michael.h"
#include "GameFramework//ProjectileMovementComponent.h"
#include "Actors/Enemy.h"
#include "UObject/ConstructorHelpers.h" // FOR POOR BAD HABIT

// Sets default values
AProjectile::AProjectile() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sphereRadius = 25.f;
	SphereCollision = CreateDefaultSubobject<USphereComponent>("sphereCollision");
	SphereCollision->InitSphereRadius(sphereRadius);
	SetRootComponent(SphereCollision);

	 
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("SphereMesh");
	SphereMesh->SetCollisionProfileName("NoCollision");
	SphereMesh->SetupAttachment(SphereCollision);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	projectileMovement->SetUpdatedComponent(SphereCollision);
	projectileMovement->InitialSpeed = 1900.f;
	projectileMovement->MaxSpeed = 1900.f;
	projectileMovement->ProjectileGravityScale = 0.f;
	InitialLifeSpan = 3.f;

	SphereMesh->OnComponentHit.AddDynamic(this, &AProjectile::BindToHitFunction);

	//The lines below will not compile
	//sphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::BindToHitFunction);


	///Start bad habit
	// Only do this here never again

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	SphereMesh->SetStaticMesh(Asset.Object);

	//End bad habit
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	// using 5/6
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnHit);
}
// Called every frame
void AProjectile::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
}

void AProjectile::FireInDirection(const FVector& ShootDirection)
{
	projectileMovement->Velocity = ShootDirection * projectileMovement->InitialSpeed;
}

void AProjectile::BindToHitFunction(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	UE_LOG(Game, Log, TEXT("THis will never get called this is the hit delegate not the overlap one"));
}

void AProjectile::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& hit)
{
	AEnemy* enemy = Cast<AEnemy>(otherActor);
	if (enemy)
	{
		UE_LOG(Projectile, Verbose, TEXT("Dealing Damage to Enemy"));
		//deal damage method call
		//Destroy(); // Destroy dead actor
	} else UE_LOG(Projectile, Verbose, TEXT("Failed to Deal Damage"));
}
