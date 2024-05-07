// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "DefaultEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ACTGDFPS502_API ADefaultEnemy : public AEnemyBase
{
	GENERATED_BODY()
		
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	class USphereComponent* PlayerDetectionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	class UStaticMeshComponent* EntityMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	class UStaticMeshComponent* EntityWireframeBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Randomise Position")
	bool ShouldRandomiseRotation = true;

	void BeginPlay() override;

	ADefaultEnemy();
	
};
