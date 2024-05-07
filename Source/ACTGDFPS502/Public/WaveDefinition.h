// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include <ACTGDFPS502/WaveSpawnDefinition.h>
#include "WaveDefinition.generated.h"

/**
 * 
 */
UCLASS()
class ACTGDFPS502_API UWaveDefinition : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave Definition")
	TSubclassOf<AWaveSpawnDefinition> WaveFormation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave Definition")
	float PercentChanceToSpawn;
};
