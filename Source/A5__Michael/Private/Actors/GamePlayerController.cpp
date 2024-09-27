// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GamePlayerController.h"

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	this->SetInputMode(InputMode);
}
