// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePickup.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/BasePlayer.h"
#include "Actors/BaseCharacter.h"


// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

	BoxCollision->SetCollisionProfileName("OverlapAll");
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::HandleOverlap);

	PickupEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PickupEffect"));
	PickupEffect->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePickup::HandleOverlap(UPrimitiveComponent* OverLappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CanPickup(OtherActor))
	{
		ABasePlayer* PlayerCharacter = Cast<ABasePlayer>(OtherActor);
		if (PlayerCharacter)
		{
			HandlePickup(OtherActor, SweepResult);
			HandlePostPickup();
		}
	}
}

bool ABasePickup::CanPickup(AActor* OtherActor)
{
	if (OtherActor)
	{
		return true;
	}
	return false;
}

void ABasePickup::HandlePickup(AActor* OtherActor, const FHitResult SweepResult)
{

}

void ABasePickup::HandlePostPickup()
{
	Destroy();
}

