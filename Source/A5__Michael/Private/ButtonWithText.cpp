// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonWithText.h"
// Components
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UButtonWithText::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (Information)
	{
		Information->SetText(Info);
	}
}

void UButtonWithText::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackgroundButton)
	{
		BackgroundButton->OnClicked.AddDynamic(this, &UButtonWithText::HandleClicked);
	}
}

void UButtonWithText::HandleClicked()
{
	onButtonClicked.Broadcast();
}
