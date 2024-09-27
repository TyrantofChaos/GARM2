// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ResultMenu.h"
#include "CodeGameInstance.h"
#include "ButtonWithText.h"
// Components
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
// Kismet
#include "Kismet/GameplayStatics.h"

void UResultMenu::SetWin()
{
	if (ResultsSwitch)
	{
		ResultsSwitch->SetActiveWidgetIndex(1); // 1 = Win
	}

	if (ButtonArea)
	{
		ButtonArea->SetVisibility(ESlateVisibility::Hidden);
	}

	AddToViewport();
	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &UResultMenu::LoadMainMenu, 2.f, false);
}

void UResultMenu::ShowLose()
{
	if (ResultsSwitch)
	{
		ResultsSwitch->SetActiveWidget(0); // 0 = Lose
	}

	if (ButtonArea)
	{
		ButtonArea->SetVisibility(ESlateVisibility::Visible);
	}

	AddToViewport();
}

void UResultMenu::LoadMainMenu()
{
	GameInstance = Cast<UCodeGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance)
	{
		GameInstance->LoadMainMenu();
	}
}

void UResultMenu::RestartGame()
{
	GameInstance = Cast<UCodeGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance)
	{
		GameInstance->LoadCurrentLevel();
	}
}

void UResultMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (MainMenuButton)
	{
		MainMenuButton->onButtonClicked.AddDynamic(this, &UResultMenu::OnMainMenuButtonClicked);
	}if (RestartButton)
	{
		RestartButton->onButtonClicked.AddDynamic(this, &UResultMenu::OnRestartButtonClicked);
	}
}

void UResultMenu::OnMainMenuButtonClicked()
{
	LoadMainMenu();
}

void UResultMenu::OnRestartButtonClicked()
{
	RestartGame();
}
