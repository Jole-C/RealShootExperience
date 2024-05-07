// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EnemySpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHandleEnemySpawningSignature, FVector, SpawnerLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPreEnemySpawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPostEnemySpawn);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTGDFPS502_API UEnemySpawner : public USceneComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Timer")
	float SpawnPerWaveCooldownSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Timer")
	float WaveCooldownSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Control")
	int EnemySpawnsPerWave;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Control")
	bool LoopInfinitely;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner Control")
	bool IsSpawningEnemies = false;

	UPROPERTY(BlueprintAssignable, Category = "Spawner Control");
	FHandleEnemySpawningSignature OnEnemySpawn;

	UPROPERTY(BlueprintAssignable, Category = "Pre Spawn");
	FPreEnemySpawn PreEnemySpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pre Spawn")
	float NumberOfSecondsBeforeSpawnToTrigger;

	UPROPERTY(BlueprintAssignable, Category = "Post Spawn");
	FPostEnemySpawn PostEnemySpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Post Spawn")
	float NumberOfSecondsAfterSpawnToTrigger;

	UFUNCTION(BlueprintCallable, Category = "Spawner Control")
	void BeginWave();

	UEnemySpawner();

protected:
	virtual void BeginPlay() override;
	void SpawnEnemies();
	void PreSpawn();
	void PostSpawn();
	virtual void HandleSpawnLogic();
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	int CurrentEnemiesToSpawn;

	FTimerHandle WaveTimerHandle;
	FTimerHandle PerWaveTimerHandle;

	FTimerHandle PreSpawnHandle;
	FTimerHandle PostSpawnHandle;
};


