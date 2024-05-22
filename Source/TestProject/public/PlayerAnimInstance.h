// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerAnim")
		bool isInAir = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerAnim")
		bool isPistol = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerAnim")
		bool isRifle = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerAnim")
		bool isSprint = false;
};
