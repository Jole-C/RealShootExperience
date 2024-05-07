// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeapon.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ACTGDFPS502Character.h"
#include "GameFramework/PlayerController.h"
#include "Public/ScoreManager.h"
#include <Kismet/GameplayStatics.h>

void AWeaponBase::Fire_Implementation()
{
}

void AWeaponBase::HandleClip()
{
	CanFire = false;

	if (CurrentClip > 1)
	{
		GetWorld()->GetTimerManager().SetTimer(
			FireCooldownTimerHandle,
			this,
			&AWeaponBase::SetCanFire,
			FireCooldownTime,
			false
		);
	}

	if (UsesClip == true)
	{
		CurrentClip -= 1;

		if (CurrentClip <= 0)
		{
			GetWorld()->GetTimerManager().SetTimer(
				ReloadTimerHandle,
				this,
				&AWeaponBase::ReloadClip,
				ClipReloadTime,
				false
			);
		}
	}

	UpdateHud();
}

void AWeaponBase::UpdateHud_Implementation()
{
}

void AWeaponBase::OnWeaponHitVisuals_Implementation(FVector OnWeaponHit)
{
}

AWeaponBase::AWeaponBase()
{
	MuzzleOffset = CreateDefaultSubobject<USphereComponent>(TEXT("MuzzlePosition"));
	MuzzleOffset->SetupAttachment(EntityMesh);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	CharacterReference = Cast<AACTGDFPS502Character>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (APlayerController* PlayerController = Cast<APlayerController>(CharacterReference->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AWeaponBase::Fire);
		}
	}

	ScoreManagerReference = (AScoreManager*)UGameplayStatics::GetActorOfClass(GetWorld(), AScoreManager::StaticClass());

	UpdateHud();
}

void AWeaponBase::ReloadClip()
{
	CurrentClip = MaxClip;
	SetCanFire();
	UpdateHud();
}

void AWeaponBase::SetCanFire()
{
	CanFire = true;
	UpdateHud();
}

void AWeaponBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsValid(this))
	{
		GetWorld()->GetTimerManager().ClearTimer(FireCooldownTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle);
	}
}

void AWeaponBase::ShakeCamera()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector PlayerPawnLocation = PlayerPawn->GetActorLocation();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerCameraManager->StartCameraShake(ShakeClass, ShakeScale);
}