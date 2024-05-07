// Copyright Epic Games, Inc. All Rights Reserved.

#include "ACTGDFPS502Character.h"
#include "ACTGDFPS502Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/World.h"
#include "PlayerWeapon.h"
#include "GameFramework/CharacterMovementComponent.h"

//////////////////////////////////////////////////////////////////////////
// AACTGDFPS502Character

void AACTGDFPS502Character::SetPlayerInvulnerable()
{
	PlayerInvulnerable = true;

	GetWorld()->GetTimerManager().SetTimer(
		InvulnerabilityTimerHandle,
		FTimerDelegate::CreateLambda([&]
		{
			PlayerInvulnerable = false;
		}),
		PlayerInvulnerabilityTimeSeconds,
		false
	);
}

void AACTGDFPS502Character::TriggerComboBuff_Implementation()
{
}

AACTGDFPS502Character::AACTGDFPS502Character()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	WeaponAttachment = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttachment"));
	WeaponAttachment->SetupAttachment(FirstPersonCameraComponent);
}

void AACTGDFPS502Character::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	ReplaceWeapon(DefaultWeapon);
}

void AACTGDFPS502Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AACTGDFPS502Character::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AACTGDFPS502Character::Look);
	}
}

void AACTGDFPS502Character::ReplaceWeapon(TSubclassOf<AWeaponBase> newWeapon)
{
	if (currentWeapon != nullptr)
	{
		currentWeapon->Destroy();
	}

	UWorld* world = GetWorld();
	FRotator weaponRotation = FRotator(0, -90, 0);
	FQuat weaponRotationQuat = FQuat(weaponRotation);

	currentWeapon = world->SpawnActor<AWeaponBase>(newWeapon);
	currentWeapon->AttachToComponent(this->WeaponAttachment,FAttachmentTransformRules::SnapToTargetIncludingScale);
	currentWeapon->AddActorLocalRotation(weaponRotationQuat, false, 0);
}

void AACTGDFPS502Character::AddForce(FVector forceToAdd)
{
	GetCharacterMovement()->Launch(forceToAdd);
}

void AACTGDFPS502Character::Move(const FInputActionValue& Value)
{
	if (IsPlayerAlive == false)
	{
		return;
	}

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AACTGDFPS502Character::Look(const FInputActionValue& Value)
{
	if (IsPlayerAlive == false)
	{
		return;
	}

	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}