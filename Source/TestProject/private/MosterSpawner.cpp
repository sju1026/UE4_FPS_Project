// Fill out your copyright notice in the Description page of Project Settings.


#include "MosterSpawner.h"
#include <UObject/ConstructorHelpers.h>
#include <Math/RandomStream.h>
#include <Kismet/GameplayStatics.h>

#include <PlayerCharacter.h>

// Sets default values
AMosterSpawner::AMosterSpawner()
{
	OnActorBeginOverlap.AddDynamic(this, &AMosterSpawner::EnterActor);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	RootComponent = trigger;

	trigger->SetSphereRadius(spanwerRadius);

	static ConstructorHelpers::FClassFinder<AMonster>monster_spawn_1(TEXT("Blueprint'/Game/_My/Blueprints/Mosters/BP_Spawn_Monster.BP_Spawn_Monster_C'"));
	if (monster_spawn_1.Succeeded()) {
		monsterCalsses.Add(monster_spawn_1.Class);
	}

	static ConstructorHelpers::FClassFinder<AMonster>monster_spawn_2(TEXT("Blueprint'/Game/_My/Blueprints/Mosters/BP_Spawn_Monster2.BP_Spawn_Monster2_C'"));
	if (monster_spawn_2.Succeeded()) {
		monsterCalsses.Add(monster_spawn_2.Class);
	}
}

// Called when the game starts or when spawned
void AMosterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMosterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMosterSpawner::EnterActor(AActor* overlappedActor, AActor* otherActor)
{
	if (otherActor->IsA(APlayerCharacter::StaticClass())) {
		APlayerCharacter* player = Cast<APlayerCharacter>(otherActor);

		if (spawnedMonsterNum != spawnNum) {
			FDateTime Now = FDateTime::Now();
			int32 Seed = Now.GetSecond() + Now.GetMillisecond();
			FRandomStream RandomStream(Seed);

			int actorSpawnRandomRange_Min_X = GetActorLocation().X - spanwerRadius;
			int actorSpawnRandomRange_Max_X = GetActorLocation().X + spanwerRadius;

			int32 randomNumber_X = RandomStream.RandRange(actorSpawnRandomRange_Min_X, actorSpawnRandomRange_Max_X);

			int actorSpawnRandomRange_Min_Y = GetActorLocation().Y - spanwerRadius;
			int actorSpawnRandomRange_Max_Y = GetActorLocation().Y + spanwerRadius;

			int32 randomNumber_Y = RandomStream.RandRange(actorSpawnRandomRange_Min_Y, actorSpawnRandomRange_Max_Y);

			FVector spawnLocation = FVector(randomNumber_X, randomNumber_Y, GetActorLocation().Z + 3.0f);

			FActorSpawnParameters params;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			if (monsterCalsses.Num() != 0) {
				GetWorld()->SpawnActor<AMonster>(monsterCalsses[0], spawnLocation, GetActorRotation(), params);
				spawnedMonsterNum++;
			}
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("Monster Max"));
		}
	}
}