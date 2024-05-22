// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <BaseCharacter.h>

#include "Gun.generated.h"

UCLASS()
class TESTPROJECT_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun(const class FObjectInitializer& ObjectInitializer);

	// =================== Inventory ===================
	void SetOwningPawn(ABaseCharacter* newOwner);
	void AttachMeshToPawn();
	void OnEquip(const AGun* lastGun);
	void OnUnEquip();
	// =================================================

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USkeletalMeshComponent* gunMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* projectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		TSubclassOf<class AProjectile> projectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon State", meta = (AllowPrivateAccess = true))
		float maxRange = 10000.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class ABaseCharacter* baseCh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon State")
		float gunDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon State")
		float damagePlus = 0.0f;

	void Fire();

private:
	AController* GetOwnerController() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon State", meta = (AllowPrivateAccess = true))
		class APlayerCharacter* player;
};
