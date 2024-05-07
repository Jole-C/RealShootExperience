// Fill out your copyright notice in the Description page of Project Settings.


#include "BombSpawnerEnemy.h"
#include "DrawDebugHelpers.h"

ABombSpawnerEnemy::ABombSpawnerEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	TargetFootUpperLeft = CreateDefaultSubobject<USceneComponent>(TEXT("Upper Left Foot Position Target"));
	TargetFootUpperRight = CreateDefaultSubobject<USceneComponent>(TEXT("Upper Right Foot Position Target"));
	TargetFootLowerLeft = CreateDefaultSubobject<USceneComponent>(TEXT("Lower Left Foot Position Target"));
	TargetFootLowerRight = CreateDefaultSubobject<USceneComponent>(TEXT("Lower Right Foot Position Target"));
	TargetTorsoPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Torso Position Target"));

	TargetFootUpperLeft->SetupAttachment(RootEnemyComponent);
	TargetFootLowerRight->SetupAttachment(RootEnemyComponent);
	TargetFootUpperRight->SetupAttachment(RootEnemyComponent);
	TargetFootLowerLeft->SetupAttachment(RootEnemyComponent);
	TargetTorsoPosition->SetupAttachment(RootEnemyComponent);

	EnemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Enemy Mesh"));
	EnemyMesh->SetupAttachment(RootEnemyComponent);
	WireframeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Wireframe Mesh"));
	WireframeMesh->SetupAttachment(EnemyMesh);
}

void ABombSpawnerEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ABombSpawnerEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
