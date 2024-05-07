// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"
#include "../EnemySpawnWarning.h"
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>

AWaveManager::AWaveManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWaveManager::RegisterEnemy(AEnemyBase* EnemyReference)
{
	EnemyReferences.Add(EnemyReference);
	TotalEnemies += 1; 
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Registered Enemy - Current Enemies %d"), TotalEnemies));
}

void AWaveManager::UnregisterEnemy(AEnemyBase* EnemyReference)
{
	if (EnemyReferences.Contains(EnemyReference))
	{
		TotalEnemies -= 1;
	}

	EnemyReferences.RemoveSingle(EnemyReference);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Unregistered Enemy - Current Enemies %d"), TotalEnemies));
}

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer
	(
		DifficultyIncreaseTimerHandle,
		this,
		&AWaveManager::IncreaseDifficulty,
		1,
		true
	);

	GetWorld()->GetTimerManager().SetTimer
	(
		StartManagerTimerHandle,
		this,
		&AWaveManager::SpawnWave,
		WaveManagerStartSeconds,
		false
	);

	GetWorld()->GetTimerManager().SetTimer
	(
		RandomisedEnemySpawnTimerHandle,
		this,
		&AWaveManager::StartRandomWave,
		TimeUntilRandomWaveStartSeconds,
		false
	);	
	
	for (int i = 0; i < EnemyDefinitionsForRandomSpawn.Num() - 1; i++)
	{
		UEnemySpawnDefinition* definition = EnemyDefinitionsForRandomSpawn[i];

		for (int DefinitionsToAdd = 0; DefinitionsToAdd < definition->SpawnPercentageChance; DefinitionsToAdd++)
		{
			PossibleEnemyChoices.Add(definition);
		}
	}

	MaxWaveSpawnTimePerSecond = StartingMaxTimeBetweenWavesSeconds;
	MinWaveSpawnTimePerSecond = StartingMinTimeBetweenWavesSeconds;
}

void AWaveManager::Tick(float DeltaTime)
{
	if (TotalEnemies > MaximumEnemyCap && DisableWaveSpawning == false)
	{
		GetWorld()->GetTimerManager().ClearTimer(PerWaveTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(RandomisedEnemySpawnTimerHandle);
		DisableWaveSpawning = true;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Disabled enemy spawning."));
	}

	if (TotalEnemies <= MaximumEnemyCap && DisableWaveSpawning == true)
	{
		DisableWaveSpawning = false;
		StartNewWave();
		StartRandomWave();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Enabled enemy spawning."));
	}

	if (HasSpawnedWave == true)
	{
		if (IsValid(SpawnedWaveReference) == false)
		{
			HasSpawnedWave = false;
			StartNewWave();
		}
	}

	if (Difficulty > DifficultyThresholdForCommonWaveIncrement * (MaxCommonWaveChoice + 1))
	{
		MaxCommonWaveChoice += 1;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Increased max common wave choice..."));
	}

	if (RareWaveDifficulty > DifficultyThresholdForRareWaveIncrement * (MaxRareWaveChoice + 1))
	{
		MaxRareWaveChoice += 1;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Increased max rare wave choice..."));
	}

	if (Difficulty == MinDifficultyBeforeRareWaveSpawn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Enabled rare wave spawn."));
	}
}

void AWaveManager::IncreaseDifficulty()
{
	Difficulty += 1;

	if (Difficulty > MinDifficultyBeforeRareWaveSpawn)
	{
		RareWaveDifficulty += 1;
	}

	MaxWaveSpawnTimePerSecond -= TimeBetweenWavesDecreasePerSecond;
	MinWaveSpawnTimePerSecond -= TimeBetweenWavesDecreasePerSecond;
}

void AWaveManager::StartNewWave()
{
	GetWorld()->GetTimerManager().SetTimer
	(
		PerWaveTimerHandle,
		this,
		&AWaveManager::SpawnWave,
		CalculateWaveTimePerSecond(),
		false
	);
}

void AWaveManager::SpawnRandomEnemy()
{
	UEnemySpawnDefinition* EnemySpawnDefinition = PossibleEnemyChoices[FMath::RandRange(0, PossibleEnemyChoices.Num() - 1)];

	FTransform EnemySpawnTransform;
	EnemySpawnTransform.SetTranslation(FVector(FMath::RandRange(-6000, 6000), FMath::RandRange(-6000, 6000), FMath::RandRange(1120, 1600)));
	EnemySpawnTransform.SetScale3D(FVector(1, 1, 1));

	AEnemySpawnWarning* EnemyWarning = GetWorld()->SpawnActorDeferred<AEnemySpawnWarning>(EnemySpawnWarningBlueprint, EnemySpawnTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	EnemyWarning->SpawnDefinition = EnemySpawnDefinition;
	UGameplayStatics::FinishSpawningActor(EnemyWarning, EnemySpawnTransform);

	GetWorld()->GetTimerManager().SetTimer
	(
		RandomisedEnemySpawnTimerHandle,
		this,
		&AWaveManager::SpawnRandomEnemy,
		MaximumTimeBetweenRandomSpawnSeconds,
		false
	);
}

float AWaveManager::CalculateWaveTimePerSecond()
{
	MinWaveSpawnTimePerSecond = FMath::Clamp(MinWaveSpawnTimePerSecond, StartingMinTimeBetweenWavesSeconds, AbsoluteMinTimeBetweenWavesSeconds);
	MaxWaveSpawnTimePerSecond = FMath::Clamp(MaxWaveSpawnTimePerSecond, StartingMaxTimeBetweenWavesSeconds, AbsoluteMaxTimeBetweenWavesSeconds);
	
	return FMath::RandRange(MinWaveSpawnTimePerSecond, MaxWaveSpawnTimePerSecond);
}

void AWaveManager::Destroyed()
{
	GetWorld()->GetTimerManager().ClearTimer(DifficultyIncreaseTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(StartManagerTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(PerWaveTimerHandle);
}

void AWaveManager::SpawnWave()
{
	if (DisableWaveSpawning == true)
	{
		return;
	}

	UWaveDefinition* ChosenSpawn;

	if (Difficulty < MinDifficultyBeforeRareWaveSpawn)
	{
		ChosenSpawn = PickWaveDefinition(CommonWaves, MaxCommonWaveChoice);
	}
	else
	{
		bool PickRareWave = UKismetMathLibrary::RandomBoolWithWeight(PercentageChanceForRareWaveToSpawn/100);

		if (PickRareWave == false)
		{
			ChosenSpawn = PickWaveDefinition(CommonWaves, MaxCommonWaveChoice);
		}
		else
		{
			ChosenSpawn = PickWaveDefinition(RareWaves, MaxRareWaveChoice);
		}
	}

	SpawnedWaveReference = GetWorld()->SpawnActor<AWaveSpawnDefinition>(ChosenSpawn->WaveFormation, FVector(0, 0, 1420), FRotator(0, 0, 0));
	HasSpawnedWave = true;
}

void AWaveManager::StartRandomWave()
{
	GetWorld()->GetTimerManager().SetTimer
	(
		RandomisedEnemySpawnTimerHandle,
		this,
		&AWaveManager::SpawnRandomEnemy,
		TimeUntilRandomWaveStartSeconds,
		false
	);
}

UWaveDefinition* AWaveManager::PickWaveDefinition(TArray<UWaveDefinition*> ArrayToPickFrom, double ArrayThreshold)
{
	int ClampedThreshold = FMath::Floor(FMath::Clamp(ArrayThreshold, 0, ArrayToPickFrom.Num() - 1));
	return ArrayToPickFrom[FMath::RandRange(0, ClampedThreshold)];
}
