// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "DroneSpawnerEnemy.generated.h"
/**
 * 
 */

UENUM(BlueprintType)
enum class EDroneSpawnerState : uint8
{
	SPAWNING UMETA(DisplayName="When this enemy spawns"),
	LOOK_AT_PLAYER UMETA(DisplayName="Looking"),
	SPAWN_ENEMIES UMETA(DisplayName="Spawning enemies"),
	PRE_SPAWN_ENEMIES UMETA(DisplayName = "Before spawning..."),
	POST_SPAWN_ENEMIES UMETA(DisplayName = "...after spawning"),
	ATTACKING UMETA(DisplayName = "Attacking")
};

UCLASS()
class ACTGDFPS502_API ADroneSpawnerEnemy : public AEnemyBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float InputDeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	ADroneSpawnerEnemy();

private:
	UFUNCTION(BlueprintCallable, Category = "Behaviour", Meta = (AllowPrivateAccess = "true"))
	void LookAtLocation(FVector Location);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behaviour", Meta = (AllowPrivateAccess = "true"))
	float DeltaSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour", Meta = (AllowPrivateAccess = "true"))
	float TimeUntilSpawnEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour", Meta = (AllowPrivateAccess = "true"))
	float MinimumPlayerDistanceForAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behaviour", Meta = (AllowPrivateAccess = "true"))
	float HeadMoveSpeed = 2.0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behaviour", Meta = (AllowPrivateAccess = "true"))
	float HeadLookSpeed = 4.0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Visuals", Meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visuals", Meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* WireframeMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behaviour", Meta = (AllowPrivateAccess = "true"))
	FVector TargetHeadLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour", Meta = (AllowPrivateAccess = "true"))
	FVector DefaultHeadLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behaviour", Meta = (AllowPrivateAccess = "true"))
	FVector TargetHeadLookLocation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behaviour", Meta = (AllowPrivateAccess = "true"))
	USceneComponent* HeadTargetRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behaviour", Meta = (AllowPrivateAccess = "true"))
	EDroneSpawnerState EnemyState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behaviour", Meta = (AllowPrivateAccess = "true"))
	USceneComponent* HeadTarget;

	FTimerHandle SpawnEnemiesTimer;

};
