// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeMainMenu.h"
#include "CodeGameInstance.h"
#include "Components/Button.h"
#include "ButtonWithText.h"
// Kismet
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UCodeMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton)
	{
		StartButton->onButtonClicked.AddDynamic(this, &UCodeMainMenu::OnStartClicked);
	}
	if (QuitButton)
	{
		QuitButton->onButtonClicked.AddDynamic(this, &UCodeMainMenu::OnQuitClicked);
	}

	UGameInstance* GI = UGameplayStatics::GetGameInstance(this);
	GameInstance = Cast<UCodeGameInstance>(GI);

	if (!GameInstance)
	{
		UKismetSystemLibrary::PrintString(this, TEXT("Wrong game instance, we need the blueprint version"), true, true, FLinearColor(0.f, 0.66f, 1.f, 1.f), 2.f);
	}
}

void UCodeMainMenu::OnStartClicked()
{
	if (GameInstance)
	{
		GameInstance->LoadFirstLevel();
	}
}

void UCodeMainMenu::OnQuitClicked()
{
	if (GameInstance)
	{
		GameInstance->QuitGame();
	}
}
