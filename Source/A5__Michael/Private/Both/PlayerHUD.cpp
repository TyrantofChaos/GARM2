// Fill out your copyright notice in the Description page of Project Settings.

#include "Both/PlayerHUD.h"
#include "Blueprint/SlateBlueprintLibrary.h"
// Kismet
#include "Kismet/KismetTextLibrary.h"
#include <Kismet/GameplayStatics.h>
#include "Kismet/KismetMathLibrary.h"
// Header File
#include "Components/ProgressBar.h"

UPlayerHUD::UPlayerHUD(const FObjectInitializer& Objectinitializer) : Super(Objectinitializer)
{
	ColorName = FName("Color");
}

void UPlayerHUD::Tick(float DeltaTime)
{
	// Get Start and End points for Line Trace
	FGeometry CachedGeometry = Crosshair->GetCachedGeometry();
	FVector2D LocalCoordinate = FVector2D(0.f, 0.f);

	// Local to ViewP
	FVector2D PixelPosition;
	FVector2D ViewportPosition;
	USlateBlueprintLibrary::LocalToViewport(GetWorld(), CachedGeometry, LocalCoordinate, PixelPosition, ViewportPosition);

	// Get Screen POS (scaled from ABS)
	FVector2D AbsoluteSize = USlateBlueprintLibrary::GetAbsoluteSize(CachedGeometry);
	FVector2D ScaledSize = AbsoluteSize * 0.5;
	FVector2D ScreenPosition = PixelPosition + ScaledSize;

	// Deproject Screen to world
	APlayerController* OwningPlayer = GetOwningPlayer();
	FVector WorldPosition;
	FVector WorldDirection;

	bool bSuccess = UGameplayStatics::DeprojectScreenToWorld(OwningPlayer, ScreenPosition, WorldPosition, WorldDirection);

	if (bSuccess)
	{
		FVector ScaledDirection = UKismetMathLibrary::Multiply_VectorFloat(WorldDirection, 100000.f);
		EndPoint = UKismetMathLibrary::Add_VectorVector(WorldPosition, ScaledDirection);
	}

	TArray<AActor*> ActorsToIgnore;

	if (OwningPlayer)
	{
		APawn* PlayerPawn = OwningPlayer->GetPawn();
		if (PlayerPawn)
		{
			ActorsToIgnore.Add(PlayerPawn);
		}

	}


}

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
	if (Crosshair)
	{
		DynamicMaterial = Crosshair->GetDynamicMaterial();
	}
}

void UPlayerHUD::UpdateMaxAmmo(int32 NewMaxAmmo)
{
	// Not Used ATM
}

void UPlayerHUD::SetHealth(float Percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}
}

void UPlayerHUD::SetAmmo(float Current, float Max)
{
	if (CurrentAmmo)
	{
		FText CurrentAmmoText = FloatToFormattedText(Current, false, true, 1, 324, 0, 3, ERoundingMode::HalfToEven);
		CurrentAmmo->SetText(CurrentAmmoText);
	}

	if (MaxAmmo)
	{
		FText MaxAmmoText = FloatToFormattedText(Max, false, true, 1, 324, 0, 3, ERoundingMode::HalfToEven);
		MaxAmmo->SetText(MaxAmmoText);
	}
}

FText UPlayerHUD::FloatToFormattedText(float Value, bool bAlwaysSign, bool bUseGrouping, int32 MinIntegralDigits, int32 MaxIntegralDigits, int32 MinFractionalDigits, int32 MaxFractionalDigits, ERoundingMode RoundingMode)
{
	return UKismetTextLibrary::Conv_FloatToText(Value, RoundingMode, bAlwaysSign, bUseGrouping, MinIntegralDigits, MaxIntegralDigits, MinFractionalDigits, MaxFractionalDigits);
}
