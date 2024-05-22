// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Camera/CameraComponent.h>


APlayerCharacter::APlayerCharacter() {
	PrimaryActorTick.bCanEverTick = true;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->TargetArmLength = 1000.0f;
	cameraBoom->bUsePawnControlRotation = true;

	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Cam"));
	cam->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);
	cam->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;

	sprintSpeed = 700.0f;
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SpawnDefaultInventory();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* playerInput)
{
	check(playerInput);

	playerInput->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	playerInput->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	playerInput->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);
	playerInput->BindAxis("LookRight", this, &ACharacter::AddControllerYawInput);

	playerInput->BindAction("Jump", IE_Pressed, this,  &ACharacter::Jump);
	playerInput->BindAction("Weapon1", IE_Pressed, this, &APlayerCharacter::UsePistol);
	playerInput->BindAction("Weapon2", IE_Pressed, this, &APlayerCharacter::UseRifle);
	playerInput->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::GunFire);
	playerInput->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::Sprint_Start);
	playerInput->BindAction("Sprint", IE_Released, this, &APlayerCharacter::Sprint_End);

}

void APlayerCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void APlayerCharacter::MoveForward(float value) {
	AddMovementInput(GetActorForwardVector() * value);
}

void APlayerCharacter::MoveRight(float value) {
	AddMovementInput(GetActorRightVector() * value);
}

void APlayerCharacter::UsePistol() {
	PlayAnimMontage(equipPistol);
	OnChangeWeapon(0);
	pistolUse = true;
	if (rifleUse == true) {
		rifleUse = false;
		pistolUse = true;
	}
}

void APlayerCharacter::UseRifle()
{
	PlayAnimMontage(equipRifle);
	OnChangeWeapon(1);
	rifleUse = true;
	if (pistolUse == true) {
		pistolUse = false;
		rifleUse = true;
	}
}

void APlayerCharacter::Sprint_Start()
{
	isSprint = true;
	GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
}

void APlayerCharacter::Sprint_End()
{
	isSprint = false;
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

