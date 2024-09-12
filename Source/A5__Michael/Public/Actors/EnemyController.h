// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class A5__MICHAEL_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:

	AEnemyController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior Tree") UBehaviorTree* BTAsset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName PlayerKey;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UAIPerceptionComponent* AIPerception;

protected:

	virtual void BeginPlay() override;
	void Tick(float DeltaTime);
	virtual void OnPossess(APawn* pawn) override;

	UFUNCTION() void OnTargetPerceptionUpdated(AActor* UpdateActor, FAIStimulus Stimulus);

private:

	void InitializePerceptionSystem();
};
