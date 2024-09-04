// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePlayer.h"// This must be first include
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABasePlayer::ABasePlayer() 
{
	// Set Spring Arm
	springArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	springArm->SetRelativeLocation(FVector(0., 0., 60.));
	springArm->SetupAttachment(GetRootComponent());
	springArm->bUsePawnControlRotation = true;
	springArm->TargetArmLength = 300.f;

	// Set Camera
	thirdPerson = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	thirdPerson->SetupAttachment(springArm, USpringArmComponent::SocketName);
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
	// Very odd bugs happen if you forget this call
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind turning to input
	PlayerInputComponent->BindAxis("TurnRight", this, &ABasePlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnUp", this, &ABasePlayer::AddControllerPitchInput);

	// Bind Moving input
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("Strafe", this, &ABasePlayer::MoveRight);

	//Attack
	PlayerInputComponent->BindAction("AttackInput", IE_Pressed, this, &ABaseCharacter::OnFire);
}

void ABasePlayer::MoveForward(float AxisValue) 
{
	AddMovementInput(FRotator(0.f, GetControlRotation().Yaw, 0.f).Vector(), AxisValue);
}

void ABasePlayer::MoveRight(float axisValue)
{
	AddMovementInput(FRotator(0.f, GetControlRotation().Yaw, 0.f).Vector(), axisValue);
}

void ABasePlayer::DealDamage()
{
	// this can stay empty FN
}
