// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/WanderTask.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UWanderTask::UWanderTask()
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UWanderTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	FNavLocation RandomLocation;

	if (NavSystem && NavSystem->GetRandomPointInNavigableRadius(AIController->GetPawn()->GetActorLocation(), MaxDistance, RandomLocation))
	{
		BlackboardComp->SetValueAsVector(TargetLocationKey.SelectedKeyName, RandomLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
