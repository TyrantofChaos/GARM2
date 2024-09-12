// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "WanderTask.generated.h"

/**
 * 
 */
UCLASS()
class A5__MICHAEL_API UWanderTask : public UBTTaskNode
{
	GENERATED_BODY()

	UWanderTask();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = "Search") float MaxDistance;
	UPROPERTY(EditAnywhere, Category = "Blackboard") FBlackboardKeySelector TargetLocationKey;
	
};
