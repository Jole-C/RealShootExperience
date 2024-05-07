// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "EnemySplitter.generated.h"

/**
 * 
 */
UCLASS()
class ACTGDFPS502_API AEnemySplitter : public AEnemyBase
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<AEnemyBase> SplitterSegmentClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	class USceneComponent* SplitterRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	class USceneComponent* SplitterMeshRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	class UStaticMeshComponent* SplitterSegmentUpper;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UStaticMeshComponent* SplitterSegmentLower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	class UStaticMeshComponent* SplitterSegmentUpperWireframe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UStaticMeshComponent* SplitterSegmentLowerWireframe;

	AEnemySplitter();

protected:
	
	
};
