// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Rifle.h"

#include "../A5__Michael.h"

// Sets default values
ARifle::ARifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	SetRootComponent(GunMesh);

	MuzzleLoc = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	MuzzleLoc->SetupAttachment(GunMesh, TEXT("MuzzleFlashSocket"));

	ProjectileClass = AProjectile::StaticClass();

	Time = 2.f;
	ActionHappening = false;

	MaxAmmo = 6;
	CurrentAmmo = MaxAmmo;
}

// Called when the game starts or when spawned
void ARifle::BeginPlay()
{
	Super::BeginPlay();

	if (APawn* pawn = Cast<APawn>(GetParentActor()))
	{
		ParentPawn = pawn;
		UE_LOG(Rifle, Log, TEXT("Rifle attached to pawn: %s"), *pawn->GetName());
		this->ReloadAmmo();
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
	if (CanShoot())
	{
		UE_LOG(Rifle, Warning, TEXT("Attempting to Fire Gun"));
		spawnLocation = MuzzleLoc->GetComponentLocation();
		spawnRotation = ParentPawn->GetBaseAimRotation();
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = ParentPawn->GetController();
		spawnParams.Instigator = ParentPawn;

		// Spawn the projectile at the muzzle location and in the correct direction
		GetWorld()->SpawnActor<AProjectile>(ProjectileClass, FTransform(ParentPawn->GetBaseAimRotation(), GunMesh->GetSocketLocation(TEXT("MuzzleFlashSocket"))), spawnParams);

		ActionHappening = true;
		FTimerHandle timerHandle;
		GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &ARifle::ActionStopped, Time);

		onRifleFire.Broadcast();
		this->UseAmmo();
		UE_LOG(Rifle, Warning, TEXT("Gun Fired"));
	}
	

}

void ARifle::OwnerDied()
{
	OwnerAlive = true;
}

bool ARifle::CanShoot() const
{
	if (!ActionHappening)
	{
		if (CurrentAmmo > 0.f)
		{
			return true;
		}
	}
	return false;
}

FVector ARifle::GetShotLocation() const
{
	return FVector();
}

void ARifle::ActionStopped()
{
	ActionHappening = false;
	onActionStopped.Broadcast();
}

void ARifle::ReloadAmmo()
{
	if (CanReload())
	{
		CurrentAmmo = MaxAmmo;
		UE_LOG(Rifle, Log, TEXT("Ammo reloaded"));
		onAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo);
	}
}

bool ARifle::CanReload() const
{
	return CurrentAmmo < MaxAmmo;
}

void ARifle::RequestReload()
{
	if (ActionHappening) return;
	else
	{
		ActionHappening = true;
		onReloadStart.Broadcast();
	}
	
}

void ARifle::UseAmmo()
{
	CurrentAmmo = FMath::Max(CurrentAmmo - 1.f, 0.f);
	if (CurrentAmmo == 0)
	{
		ReloadAmmo();
	}
	onAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo);
}

