// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnDefinition.h"
#include "EnemySpawnWarning.generated.h"

UCLASS()
class ACTGDFPS502_API AEnemySpawnWarning : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UStaticMeshComponent* WarningMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float RandomiseRotationTimeSeconds = 0.25;

	float TimeUntilSpawnSeconds = 3;
	UEnemySpawnDefinition* SpawnDefinition;

	AEnemySpawnWarning();

protected:
	virtual void BeginPlay() override;
	void SpawnEnemy();
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	FTimerHandle RandomiseRotationTimerHandle;
	FTimerHandle SpawnEnemyTimerHandle;
};
