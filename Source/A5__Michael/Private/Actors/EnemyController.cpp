// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyController::AEnemyController()
{

}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
	if (BTAsset)
	{
		RunBehaviorTree(BTAsset);
	}
}

void AEnemyController::OnTargetPerceptionUpdated(AActor* UpdateActor, FAIStimulus Stimulus)
{

}

void AEnemyController::InitializePerceptionSystem()
{

}
