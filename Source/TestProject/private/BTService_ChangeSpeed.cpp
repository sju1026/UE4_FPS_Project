// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ChangeSpeed.h"
#include <Monster.h>
#include <MonsterAIContorller.h>

#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>

UBTService_ChangeSpeed::UBTService_ChangeSpeed() {
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Speed");
}

void UBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_momory)
{
	Super::OnBecomeRelevant(owner_comp, node_momory);
	auto const cont = owner_comp.GetAIOwner();
	AMonster* const npcBot = Cast<AMonster>(cont->GetPawn());
	npcBot->GetCharacterMovement()->MaxWalkSpeed = speed;
}

FString UBTService_ChangeSpeed::GetStaticServiceDescription() const
{
	return FString("Change the Enmey Speed");
}