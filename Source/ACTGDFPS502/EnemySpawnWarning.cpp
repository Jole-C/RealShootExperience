// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnWarning.h"
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AEnemySpawnWarning::AEnemySpawnWarning()
{
	PrimaryActorTick.bCanEverTick = false;

	WarningMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	WarningMesh->SetCollisionProfileName(TEXT("NoCollision"));
	SetRootComponent(WarningMesh);
}

void AEnemySpawnWarning::BeginPlay()
{
	Super::BeginPlay();

	WarningMesh->SetStaticMesh(SpawnDefinition->EnemyWarningMesh);
	for (int i = 0; i < WarningMesh->GetNumMaterials(); i++)
	{
		WarningMesh->SetMaterial(i, SpawnDefinition->WarningMeshMaterial);
	}
	
	SetActorScale3D(SpawnDefinition->WarningMeshScale);

	GetWorld()->GetTimerManager().SetTimer
	(
		SpawnEnemyTimerHandle,
		FTimerDelegate::CreateLambda([&]
		{
			FTransform SpawnedEnemyTransform;
			SpawnedEnemyTransform.SetLocation(GetActorLocation());
			SpawnedEnemyTransform.SetScale3D(FVector(1, 1, 1));

			AEnemyBase* EnemyReference = GetWorld()->SpawnActorDeferred<AEnemyBase>(SpawnDefinition->EnemyToSpawn, SpawnedEnemyTransform, GetOwner(), nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
			UGameplayStatics::FinishSpawningActor(EnemyReference, SpawnedEnemyTransform);

			Destroy();
		}),
		TimeUntilSpawnSeconds,
		false
	);

	GetWorld()->GetTimerManager().SetTimer
	(
		RandomiseRotationTimerHandle,
		FTimerDelegate::CreateLambda([&]
		{
			SetActorRotation(UKismetMathLibrary::RandomRotator());
		}),
		RandomiseRotationTimeSeconds,
		true
	);
}

void AEnemySpawnWarning::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (SpawnEnemyTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnEnemyTimerHandle);
	}

	if (RandomiseRotationTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(RandomiseRotationTimerHandle);
	}
}
