// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EnemyBase.h"
#include "BombEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ACTGDFPS502_API ABombEnemy : public AEnemyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visuals")
	UStaticMeshComponent* EnemyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visuals")
	UStaticMeshComponent* EnemyWireframeMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	bool ShouldHome = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	float FuseTimeSeconds;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Explosion")
	void Explode();
	void Explode_Implementation();

	ABombEnemy();
};
