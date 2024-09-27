// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class A5__MICHAEL_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
};
