// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include <Projectile.h>
#include <PlayerCharacter.h>

#include <Kismet/GameplayStatics.h>
#include <DrawDebugHelpers.h>
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values
AGun::AGun(const class FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	gunMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("GunMesh"));
	gunMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = gunMesh;

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	projectileSpawnPoint->SetupAttachment(gunMesh);
}

// =================== Inventory ===================

void AGun::SetOwningPawn(ABaseCharacter* newOwner)
{
	if (baseCh != newOwner) {
		baseCh = newOwner;
	}
}

void AGun::AttachMeshToPawn()
{
	if (baseCh)
	{
		USkeletalMeshComponent* PawnMesh = baseCh->GetSpesificPawnMesh();
		FName AttachPoint = baseCh->GetWeaponAttachPoint();
		gunMesh->AttachTo(PawnMesh, AttachPoint);
	}
}

void AGun::OnEquip(const AGun* lastGun)
{
	AttachMeshToPawn();
	gunMesh->SetHiddenInGame(false);
}

void AGun::OnUnEquip()
{
	gunMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	gunMesh->SetHiddenInGame(true);
}

// =================================================

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AController* AGun::GetOwnerController() const
{
	APlayerCharacter* ownerPawn = Cast<APlayerCharacter>(player);
	if (ownerPawn == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No ownerPawn"));
		return nullptr;
	}

	return ownerPawn->GetController();
}

void AGun::Fire()
{
	AController* ownerController = GetOwnerController();
	if (ownerController == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No ownerController"));
		return;
	}

	FVector actorLocation = GetActorLocation();
	FRotator actorRotation = GetActorRotation();
	ownerController->GetPlayerViewPoint(actorLocation, actorRotation);
	FVector shotDirection = -actorRotation.Vector();
	
	FVector end = actorLocation + actorRotation.Vector() * maxRange;

	FVector location = projectileSpawnPoint->GetComponentLocation();
	FRotator rotation = projectileSpawnPoint->GetComponentRotation();

	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileClass, location, rotation);
	projectile->SetOwner(this);
	UProjectileMovementComponent* projectileMovement = Cast<UProjectileMovementComponent>(projectile->projectileMovement);
	projectileMovement->Velocity = end - location;
}
