// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../DefaultEnemy.h"
#include "DroneEnemyShielded.generated.h"

UCLASS()
class ACTGDFPS502_API ADroneEnemyShielded : public ADefaultEnemy
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	float ShieldCloseTimeSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	float ShieldOpenTimeSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	float ShieldOpenDegrees;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	float ShieldCloseDegrees;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	bool IsShieldOpen = false;

	ADroneEnemyShielded();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	void ToggleShieldState();

	FTimerHandle ShieldTimerHandle;
	
};
