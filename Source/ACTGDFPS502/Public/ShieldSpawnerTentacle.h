// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "ShieldSpawnerTentacle.generated.h"

UCLASS()
class ACTGDFPS502_API AShieldSpawnerTentacle : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shield Visuals")
	USceneComponent* TentacleOrigin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shield Visuals")
	USplineComponent* Spline;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shield Visuals")
	class UNiagaraComponent* NiagaraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Visuals")
	float NumberOfSplinePoints = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Visuals")
	float PercentageDistanceFromOriginForBezierMiddle = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Visuals")
	float AmountToLowerBezierHeight = 1000;

	UFUNCTION(BlueprintCallable)
	void SetupShield();

	// Sets default values for this actor's properties
	AShieldSpawnerTentacle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void AddSplinePoints();
	void CalculateSplinePoints();

	class AEnemyBase* EnemyReference;
	class UWeakpointBase* WeakpointReference;
	AActor* OwnerEnemy;
	FVector StartingPoint;
	FVector EnemyPoint;
	FVector BezierMiddlePoint;
	TArray<FVector> SplinePoints;
};
