// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AttackPlayer.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"

const FName UAttackPlayer::ActionFinishedMessage(TEXT("ActionFinished"));

UAttackPlayer::UAttackPlayer()
{
	NodeName = TEXT("AttackPlayer");
}

EBTNodeResult::Type UAttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* ControlledPawn = AIController ? AIController->GetPawn() : nullptr;

	IAttackInterface* AttackInterface = Cast<IAttackInterface>(ControlledPawn);

	if (AttackInterface)
	{
		AttackInterface->Attack();
		OwnerComp.RegisterMessageObserver(this, ActionFinishedMessage);
		return EBTNodeResult::Succeeded;
		
	}
	return EBTNodeResult::Failed;
}

void UAttackPlayer::OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestID, bool bSuccess)
{
	if (Message == ActionFinishedMessage)
	{
		FinishLatentTask(OwnerComp, bSuccess ? EBTNodeResult::Succeeded : EBTNodeResult::Failed);
	}
}
