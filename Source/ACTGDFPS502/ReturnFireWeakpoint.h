// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeakpointBase.h"
#include "ReturnFireWeakpoint.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTGDFPS502_API UReturnFireWeakpoint : public UWeakpointBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int NumberOfBulletsToFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float ReturnFireCooldownSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	USceneComponent* ProjectileFireLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Class")
	TSubclassOf<class AACTGDFPS502Projectile> ProjectileClass;

	UReturnFireWeakpoint();

protected:

	void OnWeakpointHit() override;
	void FireProjectile();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	int currentNumberOfBulletsToFire = 0;

	FTimerHandle FireTimerHandle;
};
