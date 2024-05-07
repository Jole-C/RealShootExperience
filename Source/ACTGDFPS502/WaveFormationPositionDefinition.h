// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "EnemySpawnDefinition.h"
#include "WaveFormationPositionDefinition.generated.h"

class AEnemySpawnWarning;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTGDFPS502_API UWaveFormationPositionDefinition : public USceneComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UArrowComponent* SpawnPositionVisual;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	TSubclassOf<AEnemySpawnWarning> EnemyWarningBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy To Choose")
	TArray<UEnemySpawnDefinition*> PossibleEnemiesToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float TimeUntilSpawnSeconds = 3;

	UWaveFormationPositionDefinition();
	void SpawnEnemy();


protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
	
	AEnemySpawnWarning* SpawnedEnemyWarningReference;
	bool HasSpawned = false;
};
