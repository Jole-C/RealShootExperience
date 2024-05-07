// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeakpointBase.h"
#include "ShieldWeakpoint.generated.h"



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTGDFPS502_API UShieldWeakpoint : public UWeakpointBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float ShieldToggleSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UStaticMeshComponent* ShieldMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UStaticMeshComponent* ShieldMeshWireframe;

	UShieldWeakpoint();

protected:
	void BeginPlay() override;
	void ToggleShield();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
	void OnWeakpointHit() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	FTimerHandle ShieldToggleTimerHandle;
	bool isShielded = false;
};
