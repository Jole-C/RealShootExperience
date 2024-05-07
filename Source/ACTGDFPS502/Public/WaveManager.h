// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../EnemySpawnDefinition.h"
#include "../WaveSpawnDefinition.h"
#include "WaveDefinition.h"
#include "WaveManager.generated.h"


class AEnemySpawnWarning;

UCLASS()
class ACTGDFPS502_API AWaveManager : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waves")
	TArray<UWaveDefinition*> CommonWaves;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waves")
	TArray<UWaveDefinition*> RareWaves;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waves")
	float StartingMaxTimeBetweenWavesSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waves")
	float StartingMinTimeBetweenWavesSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waves")
	float AbsoluteMinTimeBetweenWavesSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waves")
	float AbsoluteMaxTimeBetweenWavesSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waves")
	float TimeBetweenWavesDecreasePerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Difficulty")
	float MinDifficultyBeforeRareWaveSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Difficulty")
	float PercentageChanceForRareWaveToSpawn = 15;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Difficulty")
	float DifficultyIncreaseAmountPerSecond = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Difficulty")
	float DifficultyThresholdForCommonWaveIncrement = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Difficulty")
	float DifficultyThresholdForRareWaveIncrement = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Difficulty")
	float Difficulty = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Random Spawn")
	float TimeUntilRandomWaveStartSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Random Spawn")
	float MaximumTimeBetweenRandomSpawnSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Random Spawn")
	float MinimumTimeBetweenRandomSpawnSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Random Spawn")
	TSubclassOf<AEnemySpawnWarning> EnemySpawnWarningBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Random Spawn")
	TArray<UEnemySpawnDefinition*> EnemyDefinitionsForRandomSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	int MaximumEnemyCap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	float WaveManagerStartSeconds;

	AWaveManager();
	void RegisterEnemy(AEnemyBase* EnemyReference);
	void UnregisterEnemy(AEnemyBase* EnemyReference);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Destroyed() override;
	void IncreaseDifficulty();
	void StartNewWave();
	void SpawnRandomEnemy();
	float CalculateWaveTimePerSecond();
	void SpawnWave();
	void StartRandomWave();
	UWaveDefinition* PickWaveDefinition(TArray<UWaveDefinition*> ArrayToPickFrom, double ArrayThreshold);
	
	int TotalEnemies = 0;
	TArray<AEnemyBase*> EnemyReferences;
	TArray<UEnemySpawnDefinition*> PossibleEnemyChoices;

	FTimerHandle DifficultyIncreaseTimerHandle;
	FTimerHandle StartManagerTimerHandle;
	FTimerHandle PerWaveTimerHandle;
	FTimerHandle RandomisedEnemySpawnTimerHandle;

	AWaveSpawnDefinition* SpawnedWaveReference;

	bool HasSpawnedWave = false;
	bool DisableWaveSpawning = false;

	int MaxCommonWaveChoice = 0;
	int MaxRareWaveChoice = 0;

	int MaxWaveSpawnTimePerSecond;
	int MinWaveSpawnTimePerSecond;

	int RareWaveDifficulty = 0;
};
