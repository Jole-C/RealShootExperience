// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NiagaraComponent.h"
#include "Sound/SoundCue.h"
#include "EnemyBase.generated.h"

class AACTGDFPS502Character;
class AWaveManager;
class AScoreManager;
class UAudioComponent;



UCLASS()
class ACTGDFPS502_API AEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyBase();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	int MaxEnemyHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int EnemyHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waves")
	bool ShouldRegisterWithWaveManager = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int QualifiesForCombo = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	bool ShouldAddScore = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int ScoreToAdd = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	AACTGDFPS502Character* CharacterReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "On Spawn")
	USceneComponent* TargetWorldLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root")
	USceneComponent* RootEnemyComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UNiagaraSystem* DeathExplosionSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundCue* ExplosionSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TArray<USoundCue*> DeathSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UAudioComponent* AudioComponent;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health")
	void DamageEnemy(int damageAmount);
	virtual void DamageEnemy_Implementation(int damageAmount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Death")
	void OnEnemyDestroyed();
	virtual void OnEnemyDestroyed_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlayDeathSound();

	UFUNCTION(BlueprintCallable)
	void ApplyComboAndScore();

	UFUNCTION(BlueprintCallable, Category = "Utilities")
	FVector FindRelativeSpaceOfVector(FVector InputVector);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void SpawnNiagaraDeathSystem();

	AWaveManager* WaveManagerReference;
	AScoreManager* ScoreManagerReference;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
