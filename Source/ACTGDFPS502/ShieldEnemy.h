// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Public/ShieldSpawnerTentacle.h"
#include "ShieldEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ACTGDFPS502_API AShieldEnemy : public AEnemyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	USceneComponent* TargetTentaclePosition1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	USceneComponent* TargetTentaclePosition2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	USceneComponent* TargetTentaclePosition3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	USkeletalMeshComponent* ShielderMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	USkeletalMeshComponent* ShielderMeshWireframe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UStaticMeshComponent* ShielderCore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UStaticMeshComponent* ShielderCoreWireframe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	USceneComponent* ShieldTentacleOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Spawning")
	TSubclassOf<AShieldSpawnerTentacle> ShieldTentacleClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Shield Spawning")
	TArray<AShieldSpawnerTentacle*> SpawnedShieldTentacles;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visuals | Rigged Tentacles")
	TArray<FVector> TentaclePositions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals | Rigged Tentacles")
	float TentacleRepositionTimerSeconds = 0.7;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals | Rigged Tentacles")
	float TentaclePositionRadius = 350;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals | Movement")
	float MovementFrequency = 0.005;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals | Movement")
	float MovementAmplitude = 100;

	UFUNCTION(BlueprintCallable, Category = "Shield Spawning")
	void AddShield();

	virtual void Tick(float DeltaTime) override;
	AShieldEnemy();
	void EndPlay(const EEndPlayReason::Type EndPlayReason);

private:
	TArray<USceneComponent*> TargetTentacleOrigins;
	float SplineDistance = 0;
	FTimerHandle TentacleRepositionTimerHandle;
	FVector SpawnPos;
	float angle = 0;
	float verticalOffset;

	virtual void BeginPlay() override;
	void RepositionTentacles();
};
