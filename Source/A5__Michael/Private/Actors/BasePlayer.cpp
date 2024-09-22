// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePlayer.h"// This must be first include
#include "Camera/CameraComponent.h"
#include "Actors/Rifle.h"
#include "../A5__Michael.h"
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
	thirdPerson->bUsePawnControlRotation = false;

	health = 2.f;


}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
	// Very odd bugs happen if you forget this call
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind turning to input
	PlayerInputComponent->BindAxis("TurnRight", this, &ABasePlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnUp", this, &ABasePlayer::AddControllerPitchInput);

	// Bind Moving input
	PlayerInputComponent->BindAxis("Strafe", this, &ABasePlayer::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);

	//Attack
	PlayerInputComponent->BindAction("AttackInput", IE_Pressed, this, &ABasePlayer::DealDamage);
	PlayerInputComponent->BindAction("ReloadInput", IE_Pressed, this, &ABasePlayer::Reload);
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	//HealthComponent->onDead.AddDynamic(this, &ABasePlayer::HandleDeath);
	PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		if (HUDWidgetClass)
		{
			HUDWidget = CreateWidget<UUserWidget>(PlayerController, HUDWidgetClass);
			if (HUDWidget)
			{
				HUDWidget->AddToViewport();
				PlayerHUDClass = Cast<UPlayerHUD>(HUDWidget);
			}
		}
	}
	else
	{
		UE_LOG(PlayerLog, Warning, TEXT("Need a player controller to create a widget"));
		this->Destroy();
	}

	
	HealthComponent->onHurt.AddDynamic(this, &ABasePlayer::UpdatePlayerHealth);
	HealthComponent->onDead.AddDynamic(this, &ABasePlayer::UpdatePlayerHealth);
	HealthComponent->onHeal.AddDynamic(this, &ABasePlayer::UpdatePlayerHealth);

	rifle->onAmmoChanged.AddDynamic(this, &ABasePlayer::SetHUDAmmo);
	//rifle->ReloadAmmo();
}

void ABasePlayer::MoveForward(float axisValue) 
{
	/*AddMovementInput(FRotator(0.f, GetControlRotation().Yaw, 0.f).Vector(), AxisValue);*/
	if (axisValue != 0.f)
	{
		AddMovementInput(GetActorForwardVector(), axisValue);
	}
}

void ABasePlayer::MoveRight(float axisValue)
{
	if (axisValue != 0.f)
	{
		AddMovementInput(GetActorRightVector(), axisValue);
	}


	//AddMovementInput(FRotator(0.f, GetControlRotation().Yaw, 0.f).Vector(), axisValue);
}

void ABasePlayer::Reload()
{
	if (rifle)
	{
		rifle->ReloadAmmo();
		if (characterAnimation)
		{
			UE_LOG(PlayerLog, Warning, TEXT("Playing Reload Animation"))
			characterAnimation->ReloadAnimation();
		}
			
	}
}

void ABasePlayer::DealDamage()
{
	if (rifle)
	{
		rifle->Attack();
	}
	else
	{
		UE_LOG(PlayerLog, Warning, TEXT("Rifle is nullptr! Cannot attack."));
	}
	// this can stay empty FN
}

void ABasePlayer::UpdatePlayerHealth(float Percent)
{
	PlayerHUDClass->SetHealth(Percent);
}

void ABasePlayer::SetHUDAmmo(float Current, float Max)
{
	PlayerHUDClass->SetAmmo(Current, Max);
}


