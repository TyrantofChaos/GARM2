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
	sphereCollision = CreateDefaultSubobject<USphereComponent>("sphereCollision");
	SetRootComponent(sphereCollision);
	 
	sphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("sphereMesh");
	sphereMesh->SetCollisionProfileName("NoCollision");

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	projectileMovement->UpdatedComponent = sphereCollision;
	projectileMovement->InitialSpeed = 300.f;
	projectileMovement->MaxSpeed = 300.f;
	projectileMovement->bRotationFollowsVelocity = true;
	projectileMovement->bShouldBounce = false;
	InitialLifeSpan = 3.f;
	// How to bind to a delegate
	// Get to the delegate
	// Right click and go to the declaration
	// right click the type and go to the declaration
	// Go to the end of the macro
	// Copy the number of input paramaters
	// Create a function returning void
	// Paste the input paramters
	// Define the function
	sphereMesh->OnComponentHit.AddDynamic(this, &AProjectile::BindToHitFunction);

	//The lines below will not compile
	// // Long error
	//sphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::BindToHitFunction);


	///Start bad habit
	// Only do this here never again

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	sphereMesh->SetStaticMesh(Asset.Object);

	//End bad habit
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	// using 5/6
	sphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnHit);
}
// Called every frame
void AProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
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
