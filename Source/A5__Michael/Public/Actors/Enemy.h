// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseCharacter.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class A5__MICHAEL_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:

	AEnemy();

protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
	//void Attack();



	
};
