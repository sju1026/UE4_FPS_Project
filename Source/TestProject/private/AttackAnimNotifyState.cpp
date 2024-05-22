// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAnimNotifyState.h"
#include "Monster.h"


void UAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, __FUNCTION__);
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL) {
		AMonster* monster = Cast<AMonster>(MeshComp->GetOwner());
		if (monster != NULL) {
			monster->MeleeAttack();
		}
	}
}

void UAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, __FUNCTION__);

	if (MeshComp != NULL && MeshComp->GetOwner() != NULL) {
		AMonster* monster = Cast<AMonster>(MeshComp->GetOwner());
		if (monster != NULL) {
			monster->isDuringAttack = false;
		}
	}
}