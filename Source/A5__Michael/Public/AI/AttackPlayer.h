// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AttackInterface.h"
#include "AttackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class A5__MICHAEL_API UAttackPlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UAttackPlayer();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestID, bool bSuccess) override;

private:

	static const FName ActionFinishedMessage;
};
