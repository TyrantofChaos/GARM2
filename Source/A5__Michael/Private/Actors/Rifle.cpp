// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Rifle.h"
#include "Actors/Projectile.h"
#include "../A5__Michael.h"

// Sets default values
ARifle::ARifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	SetRootComponent(GunMesh);
	MuzzleLoc = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	MuzzleLoc->SetupAttachment(GunMesh);
	MuzzleLoc->SetRelativeLocation(GunMesh->GetSocketLocation("MuzzleFlashSocket"));

	ProjectileClass = AProjectile::StaticClass();

	// Set restrictions

}

// Called when the game starts or when spawned
void ARifle::BeginPlay()
{
	Super::BeginPlay();

	if (APawn* pawn = Cast<APawn>(GetParentActor()))
	{
		ParentPawn = pawn;
		UE_LOG(Rifle, Log, TEXT("Rifle attached to pawn: %s"), *pawn->GetName());
		// reload logic here
	}
	else
	{
		UE_LOG(Rifle, Error, TEXT("Rifle needs to be owned by a pawn, but no valid parent pawn was found!"));
		this->Destroy(); // Optionally destroy if no pawn owns it
	}
}

// Called every frame
void ARifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARifle::Attack()
{
	if (!IsValid(this))
	{
		UE_LOG(Rifle, Error, TEXT("Rifle is not valid when attempting to attack!"));
		return;
	}

	if (!ParentPawn)
	{
		UE_LOG(Rifle, Error, TEXT("Cannot fire: ParentPawn is nullptr"));
		return;
	}

	UE_LOG(Rifle, Warning, TEXT("Attempting to Fire Gun"));

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = ParentPawn->GetController();
	spawnParams.Instigator = ParentPawn;

	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, FTransform(ParentPawn->GetBaseAimRotation(), GunMesh->GetSocketLocation(TEXT("MuzzleFlashSocket"))), spawnParams);

	UE_LOG(Rifle, Warning, TEXT("Gun Fired"));
}

