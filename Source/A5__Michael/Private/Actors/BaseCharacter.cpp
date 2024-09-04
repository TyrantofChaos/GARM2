// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetRelativeRotation(FRotator(0., -90., 0.));
	GetMesh()->SetRelativeLocation(FVector(0., 0., -90.));

	childActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("Child Actor"));
	childActor->SetupAttachment(GetMesh(), "PlaceWeaponHere");
	childActor->SetChildActorClass(weaponClass);

	gunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	gunMesh->SetOnlyOwnerSee(false);
	gunMesh->bCastDynamicShadow = false;
	gunMesh->CastShadow = false;

	muzzleLoc = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	muzzleLoc->SetupAttachment(gunMesh);
	muzzleLoc->SetRelativeLocation(gunMesh->GetSocketLocation("MuzzleFlashSocket"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay() 
{
	Super::BeginPlay();

	characterAnimation = Cast<UCharacterAnimation>(GetMesh()->GetAnimInstance());
	childActor->SetChildActorClass(weaponClass);
	rifle = Cast<ARifle>(childActor);
	world = GetWorld();
	gunMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("PlaceWeaponHere"));
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

