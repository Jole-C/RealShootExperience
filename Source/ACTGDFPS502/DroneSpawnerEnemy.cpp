// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneSpawnerEnemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnemyBase.h"

ADroneSpawnerEnemy::ADroneSpawnerEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootEnemyComponent);
	WireframeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Wireframe"));
	WireframeMesh->SetupAttachment(RootEnemyComponent);
	HeadTargetRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Head Target Root"));
	HeadTargetRoot->SetupAttachment(RootEnemyComponent);
	HeadTarget = CreateDefaultSubobject<USceneComponent>(TEXT("Head Target"));
	HeadTarget->SetupAttachment(HeadTargetRoot);

	Mesh->SetCollisionProfileName(TEXT("EnemyBasis"));
	WireframeMesh->SetCollisionProfileName(TEXT("NoCollision"));
}

void ADroneSpawnerEnemy::LookAtLocation(FVector Location)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(HeadTargetRoot->GetComponentLocation(), Location);
	HeadTargetRoot->SetWorldRotation(LookAtRotation);
	FVector HeadLocation = HeadTarget->GetComponentLocation();

	TargetHeadLocation = UKismetMathLibrary::VInterpTo(TargetHeadLocation, HeadLocation, DeltaSeconds, HeadMoveSpeed);
	TargetHeadLookLocation = UKismetMathLibrary::VInterpTo(TargetHeadLookLocation, Location, DeltaSeconds, HeadLookSpeed);
}

void ADroneSpawnerEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ADroneSpawnerEnemy::Tick(float InputDeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	DeltaSeconds = InputDeltaSeconds;
}

void ADroneSpawnerEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}
