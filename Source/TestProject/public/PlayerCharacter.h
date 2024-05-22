// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* cameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* cam;

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* playerInput) override;

public:
	virtual void Tick(float deltaTime) override;

	bool pistolUse = false;
	bool rifleUse = false;
	bool isSprint = false;

private:
	void MoveForward(float value);
	void MoveRight(float value);

	void UsePistol();
	void UseRifle();

	void Sprint_Start();
	void Sprint_End();
	UPROPERTY(EditAnywhere, Category = State, meta = (AllowPrivateAccess = true))
		float sprintSpeed;

	UPROPERTY(EditAnywhere, Category = Montage, meta = (AllowPrivateAccess = true))
		UAnimMontage* equipPistol;

	UPROPERTY(EditAnywhere, Category = Montage, meta = (AllowPrivateAccess = true))
		UAnimMontage* equipRifle;
};
