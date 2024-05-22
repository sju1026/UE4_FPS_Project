// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include <PlayerCharacter.h>
#include <MonsterAIContorller.h>
#include <Monster.h>
#include <blackboard_keys.h>

#include <BehaviorTree/BlackboardComponent.h>
#include <Kismet/GameplayStatics.h>

UBTTask_Attack::UBTTask_Attack(FObjectInitializer const& object_initializer) {
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::ExecuteTask(owner_comp, node_memory);

	if (owner_comp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;

	AMonster* enemy = Cast<AMonster>(owner_comp.GetAIOwner()->GetPawn());
	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (enemy == nullptr) return EBTNodeResult::Failed;

	if (FVector::Dist(enemy->GetActorLocation(), player->GetActorLocation()) <= attackRange && enemy->isAttackable == true) {
		enemy->EnemyAttack();
	}

	return EBTNodeResult::Succeeded;
}