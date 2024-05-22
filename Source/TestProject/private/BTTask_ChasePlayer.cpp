// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChasePlayer.h"
#include <MonsterAIContorller.h>
#include <blackboard_keys.h>

#include <BehaviorTree/BlackboardComponent.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>

UBTTask_ChasePlayer::UBTTask_ChasePlayer(FObjectInitializer const& object_initializer) {
	NodeName = TEXT("Player Chase");
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AMonsterAIContorller* const cont = Cast<AMonsterAIContorller>(owner_comp.GetAIOwner());
	FVector const player_location = cont->get_blackboard()->GetValueAsVector(bb_keys::target_location);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, player_location);


	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}