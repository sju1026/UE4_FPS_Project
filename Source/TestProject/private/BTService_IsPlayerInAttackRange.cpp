// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsPlayerInAttackRange.h"
#include "Monster.h"
#include <MonsterAIContorller.h>
#include <blackboard_keys.h>

#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <Kismet/GameplayStatics.h>

UBTService_IsPlayerInAttackRange::UBTService_IsPlayerInAttackRange() {
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player in Attack Range");
}

void UBTService_IsPlayerInAttackRange::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_momory)
{
	Super::OnBecomeRelevant(owner_comp, node_momory);

	AMonsterAIContorller* const cont = Cast<AMonsterAIContorller>(owner_comp.GetAIOwner());
	AMonster* const npcBot = Cast<AMonster>(cont->GetPawn());

	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	cont->get_blackboard()->SetValueAsBool(GetSelectedBlackboardKey(), npcBot->GetDistanceTo(player) <= Attack_range);
}
