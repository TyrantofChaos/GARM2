// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Widget/ResultMenu.h"
// Final Include
#include "A5__MichaelGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class A5__MICHAEL_API AA5__MichaelGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AA5__MichaelGameModeBase();
	
protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "UI") TSubclassOf<UResultMenu> ResultWidgetClass;
	UPROPERTY() UResultMenu* ResultWidget;

public:

	UFUNCTION(BlueprintCallable, Category = "GameMode") void AddEnemy(AActor* Enemy);
	UFUNCTION(BlueprintCallable, Category = "GameMode") void RemoveEnemy(AActor* Enemy);
	UFUNCTION(BlueprintCallable, Category = "GameMode") void RemovePlayer();

	UPROPERTY() class ABasePlayer* CurrentPlayer;
	UPROPERTY() class APlayerController* CurrentController;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode", meta = (AllowPrivateAccess = true)) int32 NumEnemies;
};
