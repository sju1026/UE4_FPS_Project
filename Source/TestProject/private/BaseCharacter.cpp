// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include <Components\CapsuleComponent.h>
#include <GameFramework\CharacterMovementComponent.h>

#include "BaseCharacter.h"
#include <Gun.h>

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponAttachPoint = TEXT("GunSocket");
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	health = maxHealth;
}

void ABaseCharacter::GunFire()
{
	PlayAnimMontage(fireMontage);
	if (currentWeapon != nullptr) {
		currentWeapon->Fire();
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::Dead()
{
	UE_LOG(LogTemp, Warning, TEXT("DeathFunction!"));
	isDeath = true;

	health = FMath::Min(0.f, health);

	if (GetCapsuleComponent() != nullptr)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (GetCharacterMovement() != nullptr)
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}

	DetachFromControllerPendingDestroy();

	float deathTime = PlayAnimMontage(death_AnimMontage);

	GetWorldTimerManager().SetTimer(
		deathTimer,
		FTimerDelegate::CreateLambda([this]()->void {UE_LOG(LogTemp, Warning, TEXT("Death!")); this->Destroy(); }),
		deathTime,
		false);
}

float ABaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float myGetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	myGetDamage = FMath::Min(health, myGetDamage);

	if (myGetDamage > 0.f)
	{
		health -= myGetDamage;
	}

	if (health - myGetDamage <= 0 || health <= 0)
	{
		Dead();
		if (death_AnimMontage != nullptr) {
			PlayAnimMontage(death_AnimMontage, 1.0f);
		}
	}
	else
	{
		OnHit(myGetDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HP is : %f"), health));
	}

	return myGetDamage;
}

void ABaseCharacter::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	if (DamageTaken > 0.f)
	{
		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	}
}

// =============================Inventory=============================

USkeletalMeshComponent* ABaseCharacter::GetSpesificPawnMesh() const
{
	return GetMesh();
}

FName ABaseCharacter::GetWeaponAttachPoint() const
{
	return WeaponAttachPoint;
}

void ABaseCharacter::EquipWeapon(AGun* weapon)
{
	if (weapon)
	{
		SetCurrentWeapon(weapon, currentWeapon);
	}
}

void ABaseCharacter::OnChangeWeapon(int weaponIndex)
{
	AGun* NextWeapon = inventory[weaponIndex];

	EquipWeapon(NextWeapon);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "change!");
}

void ABaseCharacter::AddWeapon(AGun* weapon)
{
	if (weapon)
	{
		inventory.AddUnique(weapon);
	}
}

void ABaseCharacter::SetCurrentWeapon(AGun* newWeapon, AGun* lastWeapon)
{
	AGun* LocalLastWeapon = NULL;
	if (lastWeapon != NULL)
	{
		LocalLastWeapon = lastWeapon;
	}
	else if (newWeapon != currentWeapon) {
		LocalLastWeapon = currentWeapon;
	}

	if (LocalLastWeapon) {
		LocalLastWeapon->OnUnEquip();
	}

	currentWeapon = newWeapon;

	if (newWeapon)
	{
		newWeapon->SetOwningPawn(this);
		newWeapon->OnEquip(lastWeapon);
	}
}

void ABaseCharacter::SpawnDefaultInventory()
{
	int32 NumWeaponClasses = defaultInventoryClasses.Num();

	for (int32 i = 0; i < NumWeaponClasses; i++)
	{
		if (defaultInventoryClasses[i]) {
			FActorSpawnParameters SpawnInfo;

			UWorld* WRLD = GetWorld();
			AGun* NewWeapon = WRLD->SpawnActor<AGun>(defaultInventoryClasses[i], SpawnInfo);
			AddWeapon(NewWeapon);
		}
	}

	if (inventory.Num() > 0)
	{
		EquipWeapon(inventory[0]);
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, "Equip!");
	}
}
// =============================Inventory=============================