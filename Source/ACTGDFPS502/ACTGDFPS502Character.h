// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ACTGDFPS502Character.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class AWeaponBase;

UENUM(BlueprintType)
enum class EComboBuffType : uint8
{
	SPEED,
	INVULNERABILITY,
	AMMO,
	NONE
};

UCLASS(config=Game)
class AACTGDFPS502Character : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	USceneComponent* WeaponAttachment;

	UPROPERTY(EditAnywhere, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponBase> DefaultWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	int PlayerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float PlayerInvulnerabilityTimeSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	bool PlayerInvulnerable = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	bool IsPlayerAlive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	float ComboBuffDurationSeconds = 7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	float PlayerWalkSpeedNoBuff = 1200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	float PlayerWalkSpeedBuff = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	EComboBuffType ComboBuffType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetPlayerInvulnerable();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReplaceWeapon(TSubclassOf<AWeaponBase> newWeapon);

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TriggerComboBuff();
	void TriggerComboBuff_Implementation();

	AACTGDFPS502Character();
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	void AddForce(FVector forceToAdd);

protected:
	virtual void BeginPlay();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	FTimerHandle InvulnerabilityTimerHandle;
	AWeaponBase* currentWeapon = nullptr;
};

