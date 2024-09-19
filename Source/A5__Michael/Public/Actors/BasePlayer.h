// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseCharacter.h"
#include "BasePlayer.generated.h"

//class USpringArmComponent;
/**
 *
 */
UCLASS()
class A5__MICHAEL_API ABasePlayer : public ABaseCharacter 
{

	GENERATED_BODY()	
	
public:

	ABasePlayer();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI") TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY() UUserWidget* HUDWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY() UPlayerHUD* PlayerHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variable) APlayerController* PlayerController;

private:

	void MoveForward(float axisValue);
	void MoveRight(float axisValue);
	void Reload();
	

public:

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) class USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera) class UCameraComponent* thirdPerson;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera) float lookUpRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera) float turnRate;	

	

	UPROPERTY(EditAnywhere, BlueprintReadOnly) float health = 100.f;

	void DealDamage();
	UFUNCTION() void UpdatePlayerHealth(float Percent);
	UFUNCTION() void SetHUDAmmo(float Current, float Max);

};
