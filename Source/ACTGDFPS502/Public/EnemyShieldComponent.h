// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "EnemyShieldComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTGDFPS502_API UEnemyShieldComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shield Visuals")
	USplineComponent* Spline;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shield Visuals")
	class UNiagaraComponent* NiagaraComponent;

	// Sets default values for this component's properties
	UEnemyShieldComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupShield();

protected:

	class AEnemyBase* EnemyReference;
	class UWeakpointBase* WeakpointReference;
	FSplinePoint StartingPoint;
	FSplinePoint EnemyPoint;

	// Called when the game starts
	virtual void BeginPlay() override;
};
