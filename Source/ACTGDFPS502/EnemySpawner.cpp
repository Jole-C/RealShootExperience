// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"


UEnemySpawner::UEnemySpawner()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	if (LoopInfinitely == true)
	{
		BeginWave();
	}
}

void UEnemySpawner::SpawnEnemies()
{
	OnEnemySpawn.Broadcast(GetComponentLocation());
	CurrentEnemiesToSpawn -= 1;

	if (CurrentEnemiesToSpawn >= 1)
	{
		GetWorld()->GetTimerManager().SetTimer(
			PerWaveTimerHandle,
			this,
			&UEnemySpawner::SpawnEnemies,
			SpawnPerWaveCooldownSeconds,
			false
		);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(
			PostSpawnHandle,
			this,
			&UEnemySpawner::PostSpawn,
			NumberOfSecondsAfterSpawnToTrigger,
			false
		);

		if (LoopInfinitely == true)
		{
			BeginWave();
		}
	}
}

void UEnemySpawner::PreSpawn()
{
	PreEnemySpawn.Broadcast();
}

void UEnemySpawner::PostSpawn()
{
	IsSpawningEnemies = false;
	PostEnemySpawn.Broadcast();
}

void UEnemySpawner::HandleSpawnLogic()
{
}

void UEnemySpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsValid(this))
	{
		GetWorld()->GetTimerManager().ClearTimer(PerWaveTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(WaveTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(PreSpawnHandle);
		GetWorld()->GetTimerManager().ClearTimer(PostSpawnHandle);
	}
}

void UEnemySpawner::BeginWave()
{
	CurrentEnemiesToSpawn = EnemySpawnsPerWave;
	IsSpawningEnemies = true;

	GetWorld()->GetTimerManager().SetTimer(
		PreSpawnHandle,
		this,
		&UEnemySpawner::PreSpawn,
		WaveCooldownSeconds - NumberOfSecondsBeforeSpawnToTrigger,
		false
	);

	GetWorld()->GetTimerManager().SetTimer(
		WaveTimerHandle,
		this,
		&UEnemySpawner::SpawnEnemies,
		WaveCooldownSeconds,
		false
	);
}

