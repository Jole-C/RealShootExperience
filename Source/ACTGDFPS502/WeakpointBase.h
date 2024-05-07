// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "NiagaraComponent.h"
#include "Components/SpotLightComponent.h"
#include "WeakpointBase.generated.h"

class AEnemyBase;
class AACTGDFPS502Character;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTGDFPS502_API UWeakpointBase : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UStaticMeshComponent* EntityWireframeBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Child attachment point")
	USceneComponent* AttachmentPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UArrowComponent* DeathExplosionDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UNiagaraSystem* DeathExplosionSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	USphereComponent* HitPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UMaterialInstance* HitMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	USpotLightComponent* Spotlight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int MaxWeakpointHealth = 3;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, Category = "Weakpoint")
	virtual void OnWeakpointHit();

	UFUNCTION(BlueprintCallable, Category = "Weakpoint")
	void SetInvulnerability(bool IsInvulnerable){Invulnerable = IsInvulnerable;}

	void CreateWeakpointDeathParticles();

public:
	AACTGDFPS502Character* CharacterReference;
	void CalculateLightIntensity();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
	void ResetDamageMaterial();
	void SetDamageMaterialResetTimer();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	AEnemyBase* enemyReference;
	int WeakpointHealth;
	FTimerHandle DamageFlashMaterialTimerHandle;
	UMaterialInstance* DefaultMaterial;
	float HitFlashTimeSeconds = 0.25;
	bool Invulnerable = false;

public:

	// Sets default values for this component's properties
	UWeakpointBase();
};