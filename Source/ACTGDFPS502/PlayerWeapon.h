// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "ActorBase.h"
#include "Sound/SoundCue.h"
#include "Camera/CameraShakeBase.h"
#include "PlayerWeapon.generated.h"

class AACTGDFPS502Character;

UCLASS()
class ACTGDFPS502_API AWeaponBase : public AActorBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet Spawning")
	USphereComponent* MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet Spawning")
	TSubclassOf<class AACTGDFPS502Projectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "References")
	class AScoreManager* ScoreManagerReference;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
	bool UsesClip = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
	int MaxClip = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int CurrentClip = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float ClipReloadTime = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float FireCooldownTime = 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
	bool CanFire = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	float ShakeScale = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundCue* FiringSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	TSubclassOf<UCameraShakeBase> ShakeClass;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bullet Spawning")
	void Fire();
	virtual void Fire_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Visuals")
	void ShakeCamera();

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void HandleClip();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Visuals")
	void UpdateHud();
	virtual void UpdateHud_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Visuals")
	void OnWeaponHitVisuals(FVector OnWeaponHit);
	virtual void OnWeaponHitVisuals_Implementation(FVector OnWeaponHit);

	AWeaponBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	AACTGDFPS502Character* CharacterReference;
	FTimerHandle ReloadTimerHandle;
	FTimerHandle FireCooldownTimerHandle;

	virtual void BeginPlay();
	void ReloadClip();
	void SetCanFire();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
