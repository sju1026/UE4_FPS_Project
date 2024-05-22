// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <Monster.h>
#include <Components/SphereComponent.h>

#include "MosterSpawner.generated.h"

UCLASS()
class TESTPROJECT_API AMosterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMosterSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere")
		USphereComponent* trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere")
		TArray<TSubclassOf<AMonster>> monsterCalsses;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere", meta = (AllowPrivateAccess = "true"))
		float spanwerRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere", meta = (AllowPrivateAccess = "true"))
		int spawnNum = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere", meta = (AllowPrivateAccess = "true"))
		int spawnedMonsterNum = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere", meta = (AllowPrivateAccess = "true"))
		float spawnTime = 0.0f;

	UFUNCTION()
		void EnterActor(class AActor* overlappedActor, class AActor* otherActor);

};
