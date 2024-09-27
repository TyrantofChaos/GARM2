// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
// Final Include
#include "CodeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class A5__MICHAEL_API UCodeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	

	UFUNCTION(BlueprintCallable) void LoadFirstLevel();
	UFUNCTION(BlueprintCallable) void QuitGame();
	UFUNCTION(BlueprintCallable) void LoadMainMenu();
	UFUNCTION(BlueprintCallable) void LoadCurrentLevel();
	UFUNCTION(BlueprintCallable) void LoadLevelSafe(int32 LevelIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Levels") int32 MainMenuIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Levels") int32 CurrentLevelIndex;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Levels") TArray<FName> GameLevels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Levels") int32 FirstLevelIndex;
	
};
