// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayerLocation.h"
#include <MonsterAIContorller.h>
#include <PlayerCharacter.h>
#include <blackboard_keys.h>

#include <BehaviorTree/BlackboardComponent.h>
#include <NavigationSystem.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>

UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(FObjectInitializer const& object_initializer) {
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	APlayerCharacter* palyer = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	AMonsterAIContorller* cont = Cast<AMonsterAIContorller>(owner_comp.GetAIOwner());

	FVector player_location = palyer->GetActorLocation();

	if (search_random) {
		FNavLocation loc;

		UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
		if (nav_sys->GetRandomPointInNavigableRadius(player_location, search_radius, loc, nullptr)) {
			cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, loc.Location);
		}
	}
	else {
		cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, player_location);
	}

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}
