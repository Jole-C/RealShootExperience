// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreManager.generated.h"

class AInterfaceController;



UCLASS()
class ACTGDFPS502_API AScoreManager : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combo")
	int BaseCombo = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combo")
	float SecondsUntilComboReset = 15;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals")
	float SecondsToSlowOnWeakpointDestruction = 0.1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals")
	float SlowPercentage = 0.3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buff")
	float ComboIncrementForPlayerBuff = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Values")
	int Score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Values")
	int Combo = 1;

	UFUNCTION(BlueprintCallable)
	void AddCombo(int ComboAmount);

	UFUNCTION(BlueprintCallable)
	void AddScore(int ScoreToAdd);

	UFUNCTION(BlueprintCallable)
	void ResetCombo();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Visuals")
	void SetComboVisuals();
	void SetComboVisuals_Implementation();

	AScoreManager();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void ResetTimeDilation();

	FTimerHandle ComboResetTimerHandle;
	FTimerHandle SlowTimerHandle;

	int NumberComboBuffs = 1;
};
