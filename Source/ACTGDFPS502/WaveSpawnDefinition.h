// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveSpawnDefinition.generated.h"

class UWaveFormationPositionDefinition;


UCLASS()
class ACTGDFPS502_API AWaveSpawnDefinition : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Spawn")
	bool RandomRotation = false;

	UFUNCTION(BlueprintCallable, Category = "Wave Spawn")
	void SpawnEnemies();

	AWaveSpawnDefinition();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	bool HaveComponentsInArrayBeenDestroyed();

	TArray<UWaveFormationPositionDefinition*> AttachedSpawnPositions;
	bool HasSpawnedPositions = false;
};
