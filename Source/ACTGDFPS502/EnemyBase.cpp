// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "WeakpointBase.h"
#include "NiagaraFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>
#include "ACTGDFPS502Character.h"
#include "public/WaveManager.h"
#include "public/ScoreManager.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"

FVector AEnemyBase::FindRelativeSpaceOfVector(FVector InputVector)
{
	FVector RelativeVector = InputVector - GetActorLocation();
	return RelativeVector;
}

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootEnemyComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root Component"));
	SetRootComponent(RootEnemyComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(RootEnemyComponent);
	AudioComponent->bOverrideAttenuation = true;

	TargetWorldLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Target World Location"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	EnemyHealth = MaxEnemyHealth;
	CharacterReference = (AACTGDFPS502Character*)UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	WaveManagerReference = (AWaveManager*)UGameplayStatics::GetActorOfClass(GetWorld(), AWaveManager::StaticClass());

	if (IsValid(WaveManagerReference) && ShouldRegisterWithWaveManager == true)
	{
		WaveManagerReference->RegisterEnemy(this);
	}

	if (ShouldAddScore == true)
	{
		ScoreManagerReference = (AScoreManager*)UGameplayStatics::GetActorOfClass(GetWorld(), AScoreManager::StaticClass());
	}
}
void AEnemyBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnEnemyDestroyed();
	SpawnNiagaraDeathSystem();
	PlayDeathSound();

	if (IsValid(WaveManagerReference) && ShouldRegisterWithWaveManager == true)
	{
		WaveManagerReference->UnregisterEnemy(this);
	}
}

void AEnemyBase::SpawnNiagaraDeathSystem()
{
	if (EnemyHealth > 0)
	{
		return;
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathExplosionSystem, GetActorLocation(), FRotator(0, 0, 0), FVector(1, 1, 1), true, true);
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::DamageEnemy_Implementation(int damageAmount)
{
}

void AEnemyBase::OnEnemyDestroyed_Implementation()
{
}

void AEnemyBase::PlayDeathSound()
{
	USoundCue* ChosenSound = DeathSounds[FMath::RandRange(0, DeathSounds.Num() - 1)];
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ChosenSound, GetActorLocation(), 1, FMath::RandRange(0.5, 1.5));
}

void AEnemyBase::ApplyComboAndScore()
{
	if (IsValid(ScoreManagerReference) && ShouldAddScore == true)
	{
		ScoreManagerReference->AddScore(ScoreToAdd);
		ScoreManagerReference->AddCombo(1);
	}
}
