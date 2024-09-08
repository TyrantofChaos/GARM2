// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseCharacter.h"
#include "Actors/Projectile.h"
#include "../A5__Michael.h"

// Sets default values
ABaseCharacter::ABaseCharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetRelativeRotation(FRotator(0., -90., 0.));
	GetMesh()->SetRelativeLocation(FVector(0., 0., -90.));

	childActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("Child Actor"));
	childActor->SetupAttachment(GetMesh(), "PlaceWeaponHere");
	childActor->SetChildActorClass(WeaponClass);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	characterAnimation = Cast<UCharacterAnimation>(GetMesh()->GetAnimInstance());
	childActor->SetChildActorClass(WeaponClass);
	rifle = Cast<ARifle>(childActor->GetChildActor());
	world = GetWorld();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::OnFire()
{
	rifle->Attack();
	/*UE_LOG(Character, Verbose, TEXT("Firing Weapon"));
	spawnRotation = GetControlRotation();
	spawnLocation = ((muzzleLoc != nullptr) ? muzzleLoc->GetComponentLocation() : GetActorLocation()) + spawnRotation.RotateVector(gunOffSet);

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	GetWorld()->SpawnActor<AProjectile>(projectileClass, spawnLocation, spawnRotation, spawnParams);*/
}

