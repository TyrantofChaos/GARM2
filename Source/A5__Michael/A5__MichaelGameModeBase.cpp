// Copyright Epic Games, Inc. All Rights Reserved.


#include "A5__MichaelGameModeBase.h"
#include "../A5__Michael.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
// Actors
#include "Actors/BaseCharacter.h"
#include "Actors/BasePlayer.h"
#include "Actors/Enemy.h"
// Kismet
#include "Kismet/GameplayStatics.h"

AA5__MichaelGameModeBase::AA5__MichaelGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	NumEnemies = 0;
	ResultWidget = nullptr;
}

void AA5__MichaelGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> BaseCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), BaseCharacters);

	for (AActor* actor : BaseCharacters)
	{
		ABasePlayer* player = Cast<ABasePlayer>(actor);
		if (player)
		{
			CurrentPlayer = player;
			player->onEndGame.AddDynamic(this, &AA5__MichaelGameModeBase::RemovePlayer);
		}
		else
		{
			AEnemy* enemy = Cast<AEnemy>(actor);
			if (enemy) AddEnemy(enemy);			
		}
	}
}

void AA5__MichaelGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AA5__MichaelGameModeBase::AddEnemy(AActor* Enemy)
{
	NumEnemies++;
	UE_LOG(GameModeLog, Warning, TEXT("Enemy Added: %s"), *Enemy->GetName());
	Enemy->OnDestroyed.AddDynamic(this, &AA5__MichaelGameModeBase::RemoveEnemy);
}

void AA5__MichaelGameModeBase::RemoveEnemy(AActor* Enemy)
{
	NumEnemies--;
	UE_LOG(GameModeLog, Warning, TEXT("Enemy Added: %s"), *Enemy->GetName());
	if (NumEnemies)
	{
		return;
	}
	UKismetSystemLibrary::PrintString(this, TEXT("You Lose"), true, true, FLinearColor(0.f, 0.66f, 1.f, 1.f), 2.f);
	UE_LOG(GameModeLog, Warning, TEXT("Inside Remove Enemy"));

	if (ResultWidgetClass && !ResultWidget)
	{
		ResultWidget = CreateWidget<UResultMenu>(GetWorld(), ResultWidgetClass);
		if (ResultWidget)
		{
			ResultWidget->SetWin();
			ResultWidget->AddToViewport();

			UE_LOG(GameModeLog, Warning, TEXT("Remove Enemy if Statement"));

			APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (playerController)
			{
				// Show Mouse Cursor
				playerController->bShowMouseCursor = true;

				// Set input to UI only
				UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(playerController, ResultWidget, EMouseLockMode::LockAlways);
			}
		}
	}

	if (CurrentPlayer)
	{
		CurrentPlayer->WinGame();
	}
}

void AA5__MichaelGameModeBase::RemovePlayer()
{
	UKismetSystemLibrary::PrintString(this, TEXT("You Win"), true, true, FLinearColor(0.f, 0.66f, 1.f, 1.f), 2.f);
	UE_LOG(GameModeLog, Warning, TEXT("Inside Remove Player"));
	TArray<AActor*> characters;

	// Get all Actors
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), characters);

	// Iterate over each character
	for (AActor* actor : characters)
	{
		actor->OnDestroyed.AddDynamic(this, &AA5__MichaelGameModeBase::RemoveEnemy);
	}

	// Create and add teh Results Widget to Viewport
	if (ResultWidgetClass && !ResultWidget)
	{
		ResultWidget = CreateWidget<UResultMenu>(GetWorld(), ResultWidgetClass);
		if (ResultWidget)
		{
			ResultWidget->ShowLose();
			ResultWidget->AddToViewport();

			// Get Player Controller
			APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

			if (playerController)
			{
				playerController->bShowMouseCursor = true;
				UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(playerController, ResultWidget, EMouseLockMode::LockAlways);
			}
			else UE_LOG(GameModeLog, Warning, TEXT("Failed to get Player Controller"));

		}
		else UE_LOG(GameModeLog, Warning, TEXT("Failed to create Result Widget"));		
	}
	else if (!ResultWidgetClass) UE_LOG(GameModeLog, Warning, TEXT("Result Widget class is not set"));

	if (CurrentPlayer) CurrentPlayer->WinGame();
}
