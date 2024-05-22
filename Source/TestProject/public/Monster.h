// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include <CombatInterface.h>
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API AMonster : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AMonster();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		FName monsterName;

	void EnemyAttack();

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
		float AttackRange = 200.0f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
		float AttackRadius = 50.0f;

	UAnimMontage* get_montage() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = State)
		bool isAttackable = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = State)
		bool isDuringAttack = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = State)
		float animTime;

	FTimerHandle attackHandle;

	void MeleeAttack();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
		UAnimMontage* montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
		float attackDamage = 0;
};
