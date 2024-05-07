// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreManager.h"
#include "../ACTGDFPS502Character.h"
#include <Kismet/GameplayStatics.h>

void AScoreManager::AddCombo(int ComboAmount)
{
	GetWorld()->GetWorldSettings()->SetTimeDilation(SlowPercentage);
	Combo += 1;
	SetComboVisuals();

	GetWorld()->GetTimerManager().SetTimer(
		SlowTimerHandle,
		this,
		&AScoreManager::ResetTimeDilation,
		SecondsToSlowOnWeakpointDestruction,
		false
	);

	GetWorld()->GetTimerManager().SetTimer(
		ComboResetTimerHandle,
		this,
		&AScoreManager::ResetCombo,
		SecondsUntilComboReset,
		false
	);

	if (Combo > NumberComboBuffs * ComboIncrementForPlayerBuff)
	{
		AACTGDFPS502Character* CharacterReference = (AACTGDFPS502Character*)UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		CharacterReference->TriggerComboBuff();
	}
}

void AScoreManager::AddScore(int ScoreToAdd)
{
	Score += ScoreToAdd * Combo;
	SetComboVisuals();
}

void AScoreManager::ResetCombo()
{
	Combo = BaseCombo;
	NumberComboBuffs = 1;
	SetComboVisuals();
}

void AScoreManager::SetComboVisuals_Implementation()
{
}

AScoreManager::AScoreManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AScoreManager::BeginPlay()
{
	Super::BeginPlay();
}

void AScoreManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ComboResetTimerHandle.IsValid() == true)
	{
		GetWorld()->GetTimerManager().ClearTimer(ComboResetTimerHandle);
	}

	if (SlowTimerHandle.IsValid() == true)
	{
		GetWorld()->GetTimerManager().ClearTimer(SlowTimerHandle);
	}
}

void AScoreManager::ResetTimeDilation()
{
	GetWorld()->GetWorldSettings()->SetTimeDilation(1);
}

