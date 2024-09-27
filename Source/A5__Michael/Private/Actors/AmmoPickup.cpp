// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AmmoPickup.h"
#include "Actors/BasePlayer.h"

AAmmoPickup::AAmmoPickup()
{
	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
	AmmoMesh->SetupAttachment(RootComponent);

	AmmoMesh->SetCollisionProfileName("OverlapAll");
	AmmoMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	AmmoMesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoPickup::OnBeginOverlap);
}

void AAmmoPickup::BeginPlay()
{
	Super::BeginPlay();
}

void AAmmoPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmmoPickup::HandlePickup(AActor* OtherActor, const FHitResult SweepResult)
{
	Super::HandlePickup(OtherActor, SweepResult);
	
	ABasePlayer* player = Cast<ABasePlayer>(OtherActor);
	if (player)
	{
		player->IncreaseMaxAmmo(5);
		Destroy();
	}
}

void AAmmoPickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CanPickup(Other))
	{
		HandlePickup(Other, SweepResult);
		HandlePostPickup();
	}
}
