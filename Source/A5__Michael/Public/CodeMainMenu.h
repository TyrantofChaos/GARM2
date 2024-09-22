// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
// Final include
#include "CodeMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class A5__MICHAEL_API UCodeMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

public:

	UPROPERTY(BlueprintReadOnly) class UCodeGameInstance* GameInstance;
	UPROPERTY(EditDefaultsOnly) class UButtonWithText* StartButton;
	UPROPERTY(EditDefaultsOnly) class UButtonWithText* QuitButton;

private:

	UFUNCTION() void OnStartClicked();
	UFUNCTION() void OnQuitClicked();
};
