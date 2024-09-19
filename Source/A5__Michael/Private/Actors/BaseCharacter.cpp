// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseCharacter.h"
#include "Both/CharacterAnimation.h"


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
	FTransform SocketTransform = GetMesh()->GetSocketTransform(TEXT("PlaceWeaponHere"));

	WeaponClass = ARifle::StaticClass();
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	characterAnimation = Cast<UCharacterAnimation>(GetMesh()->GetAnimInstance());
	childActor->SetChildActorClass(WeaponClass);
	rifle = Cast<ARifle>(childActor->GetChildActor());
	world = GetWorld();

	rifle->onRifleFire.AddDynamic(this, &ABaseCharacter::FireAnimation);
	rifle->onRifleFire.AddDynamic(this, &ABaseCharacter::OnReloadStartHandler);

	HealthComponent->onHurt.AddDynamic(this, &ABaseCharacter::HandleHurt);
	HealthComponent->onHurt.AddDynamic(this, &ABaseCharacter::HandleDead);

	characterAnimation->onReloadEnded.AddDynamic(this, &ABaseCharacter::OnReloadEndHandler);
	characterAnimation->onReloadEnded.AddDynamic(this, &ABaseCharacter::OnReloadNowHandler);
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
}

void ABaseCharacter::OnReloadEndHandler()
{
	rifle->ActionStopped();
}

void ABaseCharacter::OnReloadNowHandler()
{
	rifle->ReloadAmmo();
}

void ABaseCharacter::HandleDead(float Ratio)
{
	characterAnimation->DeathAnimation(Ratio);
	SetActorEnableCollision(false);
	// rifle the owner died
	onCharacterDeath.Broadcast();
}

void ABaseCharacter::HandleHurt(float Ratio)
{
	characterAnimation->HurtAnimation(Ratio);
}

void ABaseCharacter::DelayedDestruction()
{
	Destroy();
}

void ABaseCharacter::FireAnimation()
{
	characterAnimation->FireAnimation();
}

void ABaseCharacter::HurtAnimation(AActor* OtherActor)
{
	characterAnimation->HurtAnimation(0.f);
}

void ABaseCharacter::HandleRifleFire(AActor* OtherActor)
{
	characterAnimation->FireAnimation();
}

void ABaseCharacter::OnReloadStartHandler()
{
	characterAnimation->ReloadAnimation();
}

