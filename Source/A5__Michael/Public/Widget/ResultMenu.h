// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
// Final include
#include "ResultMenu.generated.h"

/**
 * 
 */
UCLASS()
class A5__MICHAEL_API UResultMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Game Results") void SetWin();
	UFUNCTION(BlueprintCallable, Category = "Game Results") void ShowLose();
	UFUNCTION(BlueprintCallable, Category = "Game Results") void LoadMainMenu();
	UFUNCTION(BlueprintCallable, Category = "Game Results") void RestartGame();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) class UButtonWithText* MainMenuButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) class UButtonWithText* RestartButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) class UVerticalBox* ButtonArea;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) class UWidgetSwitcher* ResultsSwitch;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) class UCodeGameInstance* GameInstance;

protected:

	virtual void NativeConstruct() override;

private:

	UFUNCTION() void OnMainMenuButtonClicked();
	UFUNCTION() void OnRestartButtonClicked();
	
};
