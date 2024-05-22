// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <Perception/AIPerceptionTypes.h>

#include "MonsterAIContorller.generated.h"

/**
 * 
 */

class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS(config = Game)
class TESTPROJECT_API AMonsterAIContorller : public AAIController
{
	GENERATED_BODY()
	
public:
	AMonsterAIContorller(FObjectInitializer const& object_initializer = FObjectInitializer::Get());

protected:

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* pawn) override;

public:

	virtual void Tick(float DeltaTime) override;
	virtual FRotator GetControlRotation() const override;

	UFUNCTION(BlueprintCallable, Category = Behavior)
		void on_target_detected(AActor* actor, FAIStimulus const stimulus);

	class UBlackboardComponent* get_blackboard() const;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behavior_tree_comp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* btree;

	class UBlackboardComponent* blackboard;
	class UAISenseConfig_Sight* sight_config;

	void setup_perception_system();
};
