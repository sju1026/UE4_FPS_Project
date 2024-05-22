// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto ownerPawn = TryGetPawnOwner();

	auto player = Cast<APlayerCharacter>(ownerPawn);

	if (player) {
		auto movement = player->GetCharacterMovement();
		isInAir = movement->IsFalling();

		isPistol = player->pistolUse;
		isRifle = player->rifleUse;
		isSprint = player->isSprint;
	}
}