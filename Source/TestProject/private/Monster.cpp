// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/BoxComponent.h>
#include <DrawDebugHelpers.h>
#include <TimerManager.h>

#include <PlayerCharacter.h>

AMonster::AMonster() {
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonster::EnemyAttack()
{
	isAttackable = false;
	animTime = PlayAnimMontage(montage);

	GetWorldTimerManager().SetTimer(
		attackHandle, 
		FTimerDelegate::CreateLambda([this]()->void {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TimerStart"));
			isAttackable = true; }),
		animTime, 
		false);

	PlayAnimMontage(montage);

}

UAnimMontage* AMonster::get_montage() const
{
	return montage;
}

void AMonster::MeleeAttack()
{
	isDuringAttack = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack"));

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.0f),
		Params);

	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 1.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);


	if (bResult) {
		if (HitResult.Actor.IsValid() && HitResult.Actor->IsA(APlayerCharacter::StaticClass())) {
			APlayerCharacter* hit_actor = Cast<APlayerCharacter>(HitResult.Actor);
			if (hit_actor->health - attackDamage < 0.0f) {
				hit_actor->PlayAnimMontage(hit_actor->death_AnimMontage);
				hit_actor->SetActorEnableCollision(false);
				// hit_actor->Die();
			}
			else
			{
				hit_actor->health -= attackDamage;
			}
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("Attack"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Player HitDamage is : %f"), hit_actor->health));
		}
	}
}
