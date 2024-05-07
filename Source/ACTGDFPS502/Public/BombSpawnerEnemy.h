// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EnemyBase.h"
#include "BombSpawnerEnemy.generated.h"
/**
 * 
 */
UCLASS()
class ACTGDFPS502_API ABombSpawnerEnemy : public AEnemyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visuals")
	USkeletalMeshComponent* EnemyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visuals")
	USkeletalMeshComponent* WireframeMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behaviour")
	FVector TorsoPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behaviour")
	USceneComponent* TargetFootUpperLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behaviour")
	USceneComponent* TargetFootUpperRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behaviour")
	USceneComponent* TargetFootLowerLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behaviour")
	USceneComponent* TargetFootLowerRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behaviour")
	USceneComponent* TargetTorsoPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour")
	TArray<FVector> CurrentFootPositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour")
	float FootMovementSpeed = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour")
	float DistanceToCountFootAsPlanted = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour")
	float DistanceBeforeMovingFoot = 170;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour")
	FVector OffsetToAddWhenPlacingFoot = FVector(170, 0, 0);

	ABombSpawnerEnemy();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
};
