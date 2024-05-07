// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeakpointBase.h"
#include "DefaultWeakpoint.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTGDFPS502_API UDefaultWeakpoint : public UWeakpointBase
{
	GENERATED_BODY()

public:
	UDefaultWeakpoint();

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OnWeakpointHit() override;
	
};
