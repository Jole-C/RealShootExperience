// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveFormationPositionDefinition.h"
#include <Kismet/KismetArrayLibrary.h>
#include "EnemyBase.h"
#include "EnemySpawnWarning.h"
#include <Kismet/GameplayStatics.h>

UWaveFormationPositionDefinition::UWaveFormationPositionDefinition()
{
	PrimaryComponentTick.bCanEverTick = true;

	SpawnPositionVisual = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Visual"));
	SpawnPositionVisual->SetRelativeRotation(FRotator(0, 90, 0));
	SpawnPositionVisual->SetupAttachment(this);
}

void UWaveFormationPositionDefinition::SpawnEnemy()
{
	if (PossibleEnemiesToSpawn.Num() == 0)
	{
		DestroyComponent();
		return;
	}

	UEnemySpawnDefinition* ChosenSpawnDefinition = PossibleEnemiesToSpawn[FMath::RandRange(0, PossibleEnemiesToSpawn.Num()-1)];

	FTransform SpawnedWarningTransform;
	SpawnedWarningTransform.SetTranslation(GetComponentLocation() + ChosenSpawnDefinition->SpawnPositionOffset);
	SpawnedWarningTransform.SetRotation(FRotator(0, 0, 0).Quaternion());
	SpawnedWarningTransform.SetScale3D(FVector(1, 1, 1));

	SpawnedEnemyWarningReference = GetWorld()->SpawnActorDeferred<AEnemySpawnWarning>(EnemyWarningBlueprint, SpawnedWarningTransform, GetOwner(), nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	SpawnedEnemyWarningReference->SpawnDefinition = ChosenSpawnDefinition;
	SpawnedEnemyWarningReference->TimeUntilSpawnSeconds = TimeUntilSpawnSeconds;
	UGameplayStatics::FinishSpawningActor(SpawnedEnemyWarningReference, SpawnedWarningTransform);

	HasSpawned = true;
}

void UWaveFormationPositionDefinition::BeginPlay()
{
	Super::BeginPlay();
}

void UWaveFormationPositionDefinition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (IsValid(SpawnedEnemyWarningReference) == false && HasSpawned == true)
	{
		DestroyComponent();
	}
}
