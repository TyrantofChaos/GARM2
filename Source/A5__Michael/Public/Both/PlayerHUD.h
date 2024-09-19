// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "PlayerHUD.generated.h"

/**
 *
 */
UCLASS()
class A5__MICHAEL_API UPlayerHUD : public UUserWidget 
{

	GENERATED_BODY()

public:

	UPlayerHUD(const FObjectInitializer& Objectinitializer);

protected:

	virtual void Tick(float DeltaTime);
	virtual void NativeConstruct() override;

public:

	UFUNCTION(BlueprintCallable, Category = "HUD") void UpdateMaxAmmo(int32 NewMaxAmmo);
	UFUNCTION(BlueprintCallable) void SetHealth(float Percent);
	UFUNCTION(BlueprintCallable) void SetAmmo(float Current, float Max);

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) class UProgressBar* HealthBar;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) class UImage* Crosshair;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly) UMaterialInstanceDynamic* DynamicMaterial;
	UPROPERTY(BlueprintReadWrite) FName ColorName;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly) FLinearColor DangerColor;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly) FLinearColor SafeColor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))UTextBlock* CurrentAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))UTextBlock* MaxAmmo;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly) FVector EndPoint;

private:

	FText FloatToFormattedText(float Value, bool bAlwaysSign, bool bUseGrouping, int32 MinIntegralDigits, int32 MaxIntegralDigits, int32 MinFractionalDigits, int32 MaxFractionalDigits, ERoundingMode RoundingMode);

};
