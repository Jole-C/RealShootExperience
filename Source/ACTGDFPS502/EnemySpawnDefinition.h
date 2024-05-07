// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyBase.h"
#include "EnemySpawnDefinition.generated.h"

/**
 * 
 */
UCLASS()
class ACTGDFPS502_API UEnemySpawnDefinition : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Warning Visuals")
	UStaticMesh* EnemyWarningMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Warning Visuals")
	FVector WarningMeshScale = FVector(1, 1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Warning Visuals")
	UMaterialInstance* WarningMeshMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Spawning")
	TSubclassOf<AEnemyBase> EnemyToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Spawning")
	FVector SpawnPositionOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Spawning")
	int SpawnPercentageChance;
};
