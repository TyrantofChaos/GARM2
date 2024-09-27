// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeGameInstance.h"
#include "../A5__Michael.h"
// Kismet
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"



void UCodeGameInstance::LoadFirstLevel()
{
	if (GameLevels.IsValidIndex(FirstLevelIndex))
	{
		UGameplayStatics::OpenLevel(this, GameLevels[FirstLevelIndex]);
	}
	else
	{
		UE_LOG(Game, Warning, TEXT("Invalid Level Index"));
	}
}

void UCodeGameInstance::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UCodeGameInstance::LoadMainMenu()
{
	if (GameLevels.IsValidIndex(MainMenuIndex))
	{
		UGameplayStatics::OpenLevel(this, GameLevels[MainMenuIndex]);
	}
	else
	{
		UE_LOG(Game, Warning, TEXT("Invalid Main Menu Index"));
	}
}

void UCodeGameInstance::LoadCurrentLevel()
{
	if (GameLevels.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(this, GameLevels[CurrentLevelIndex]);
	}
	else
	{
		UE_LOG(Game, Warning, TEXT("Invalid Current Level Index"));
	}
}

void UCodeGameInstance::LoadLevelSafe(int32 LevelIndex)
{
	if (GameLevels.IsValidIndex(LevelIndex))
	{
		CurrentLevelIndex = LevelIndex;
		UGameplayStatics::OpenLevel(this, GameLevels[LevelIndex]);
	}
	else
	{
		UE_LOG(Game, Warning, TEXT("Cannot Load Level Index %d"), LevelIndex);
	}
}
