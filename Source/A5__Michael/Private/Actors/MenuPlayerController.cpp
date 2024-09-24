// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MenuPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (MenuClass)
	{
		MenuWidget = CreateWidget<UUserWidget>(this, MenuClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();

			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(MenuWidget->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			this->SetInputMode(InputMode);
			this->bShowMouseCursor = true;
		}
	}
}
