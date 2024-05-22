// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class TESTPROJECT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UPROPERTY(VisibleAnywhere, Category = "State")
		float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		float maxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		float walkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motage")
		UAnimMontage* death_AnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motage")
		UAnimMontage* fireMontage;

#pragma region Inventory
	//============================================= Inventory =====================================================
	USkeletalMeshComponent* GetSpesificPawnMesh()const;

	FName GetWeaponAttachPoint() const;

	void EquipWeapon(class AGun* weapon);

	void OnChangeWeapon(int weaponIndex);

protected:

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		FName WeaponAttachPoint;

	TArray<class AGun*>inventory;

	void AddWeapon(class AGun* weapon);

	void SetCurrentWeapon(class AGun* newWeapon, class AGun* lastWeapon);

	void SpawnDefaultInventory();

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		TArray<TSubclassOf<class AGun>>defaultInventoryClasses;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
		class AGun* currentWeapon;
	//=============================================================================================================
#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GunFire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
		bool isDeath = false;

	FTimerHandle deathTimer;
	void Dead();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;

protected:

	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

};
