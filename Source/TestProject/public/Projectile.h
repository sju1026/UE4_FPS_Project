// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TESTPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
		UStaticMeshComponent* projectileMesh;

public:
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		class UProjectileMovementComponent* projectileMovement;

private:

	UFUNCTION()
		void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);

	UPROPERTY(EditAnywhere)
		float damage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
