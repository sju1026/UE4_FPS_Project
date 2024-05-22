// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include <Gun.h>
#include <BaseCharacter.h>
#include <Monster.h>

#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <GameFramework/DamageType.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerController.h>

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = projectileMesh;

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	projectileMovement->InitialSpeed = 10000.0f;
	projectileMovement->MaxSpeed = 10000.0f;
	projectileMovement->bShouldBounce = false;

	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	projectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Hit OtherActor
void AProjectile::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	AActor* myOwner = GetOwner();
	if (myOwner == nullptr) {
		Destroy();
		return;
	}

	AGun* currentGun = Cast<AGun>(myOwner);
	if (currentGun != nullptr) {
		damage = currentGun->gunDamage;
	}

	AController* myOwnerInstigator = myOwner->GetInstigatorController();
	UClass* damageTypeClass = UDamageType::StaticClass();

	if (otherActor && otherActor->IsA(AMonster::StaticClass())) {
		UGameplayStatics::ApplyDamage(otherActor, damage, myOwnerInstigator, this, damageTypeClass);
	}

	Destroy();
}

