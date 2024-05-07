// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveSpawnDefinition.h"
#include "WaveFormationPositionDefinition.h"

AWaveSpawnDefinition::AWaveSpawnDefinition()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWaveSpawnDefinition::BeginPlay()
{
	Super::BeginPlay();

	if (RandomRotation == true)
	{
		FRotator Rotation = FRotator(0, 0, FMath::RandRange(0, 360));
		SetActorRotation(Rotation.Quaternion());
	}

	SpawnEnemies();
}

void AWaveSpawnDefinition::Tick(float DeltaTime)
{
	if (HasSpawnedPositions == false)
	{
		return;
	}

	if (HaveComponentsInArrayBeenDestroyed() == true)
	{
		Destroy();
	}
}

bool AWaveSpawnDefinition::HaveComponentsInArrayBeenDestroyed()
{
	for (int i = 0; i < AttachedSpawnPositions.Num(); i++)
	{
		UWaveFormationPositionDefinition* Component = AttachedSpawnPositions[i];

		if (IsValid(Component) == true)
		{
			return false;
		}
	}
	
	return true;
}

void AWaveSpawnDefinition::SpawnEnemies()
{
	GetComponents(AttachedSpawnPositions);

	for (int i = 0; i < AttachedSpawnPositions.Num(); i++)
	{
		auto Definition = AttachedSpawnPositions[i];
		Definition->SpawnEnemy();
	}

	HasSpawnedPositions = true;
}