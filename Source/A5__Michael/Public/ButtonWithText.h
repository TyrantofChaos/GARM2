// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonWithText.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);

/**
 * 
 */
UCLASS()
class A5__MICHAEL_API UButtonWithText : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:

	UFUNCTION() void HandleClicked();
	UPROPERTY(meta = (BindWidget)) class UButton* BackgroundButton;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* Information;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button") FText Info;
	UPROPERTY(BlueprintAssignable, Category = "Button") FOnButtonClicked onButtonClicked;
	
};
