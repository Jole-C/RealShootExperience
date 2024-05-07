// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldEnemy.h"
#include <Kismet/KismetMathLibrary.h>

AShieldEnemy::AShieldEnemy()
{
	ShielderMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	ShielderMesh->SetupAttachment(RootEnemyComponent);
	ShielderMeshWireframe = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Wireframe"));
	ShielderMeshWireframe->SetupAttachment(ShielderMesh);
	ShielderCore = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Core Mesh"));
	ShielderCore->SetupAttachment(RootEnemyComponent);
	ShielderCoreWireframe = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Core Mesh Wireframe"));
	ShielderCoreWireframe->SetupAttachment(ShielderCore);
	TargetTentaclePosition1 = CreateDefaultSubobject<USceneComponent>(TEXT("Tentacle Target 1"));
	TargetTentaclePosition1->SetupAttachment(RootEnemyComponent);
	TargetTentaclePosition2 = CreateDefaultSubobject<USceneComponent>(TEXT("Tentacle Target 2"));
	TargetTentaclePosition2->SetupAttachment(RootEnemyComponent);
	TargetTentaclePosition3 = CreateDefaultSubobject<USceneComponent>(TEXT("Tentacle Target 3"));
	TargetTentaclePosition3->SetupAttachment(RootEnemyComponent);
	ShieldTentacleOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("Shield Spawn Point"));
	ShieldTentacleOrigin->SetupAttachment(RootEnemyComponent);

	ShielderMesh->SetCollisionProfileName(TEXT("EnemyBasis"));
	ShielderMeshWireframe->SetCollisionProfileName(TEXT("NoCollision"));
}

void AShieldEnemy::BeginPlay()
{
	Super::BeginPlay();

	TentaclePositions.SetNum(3);
	TargetTentacleOrigins.Add(TargetTentaclePosition1);
	TargetTentacleOrigins.Add(TargetTentaclePosition2);
	TargetTentacleOrigins.Add(TargetTentaclePosition3);

	for (int i = 0; i < TentaclePositions.Num(); i++)
	{
		FVector RelativePos = TargetTentacleOrigins[i]->GetRelativeLocation();
		TentaclePositions[i] = RelativePos;
	}

	GetWorld()->GetTimerManager().SetTimer(
		TentacleRepositionTimerHandle,
		this,
		&AShieldEnemy::RepositionTentacles,
		TentacleRepositionTimerSeconds,
		true,
		0.01
	);

	SpawnPos = GetActorLocation();
}

void AShieldEnemy::RepositionTentacles()
{
	for (int i = 0; i < TentaclePositions.Num(); i++)
	{
		FVector PositionTarget;
		FVector RandomVector = UKismetMathLibrary::RandomUnitVector();

		PositionTarget = TargetTentacleOrigins[i]->GetRelativeLocation() + (RandomVector * TentaclePositionRadius);
		TentaclePositions[i] = PositionTarget;
	}
}

void AShieldEnemy::AddShield()
{
	AShieldSpawnerTentacle* NewShield = GetWorld()->SpawnActor<AShieldSpawnerTentacle>(ShieldTentacleClass, FVector(0, 0, 0), FRotator(0, 0, 0));

	if (IsValid(NewShield))
	{
		SpawnedShieldTentacles.Add(NewShield);

		NewShield->TentacleOrigin->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		NewShield->TentacleOrigin->AttachToComponent(ShieldTentacleOrigin, FAttachmentTransformRules::SnapToTargetIncludingScale);
		NewShield->TentacleOrigin->SetRelativeLocation(FVector(0, 0, 0));

		NewShield->SetOwner(this);

		NewShield->SetupShield();
	}
}

void AShieldEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Destroy actor if tentacles are dead
	bool TentaclesAlive = true;

	for (AActor* Tentacle : SpawnedShieldTentacles)
	{
		TentaclesAlive &= IsValid(Tentacle);
	}

	if (TentaclesAlive == false)
	{
		Destroy();
	}

	angle += MovementFrequency;
	verticalOffset = FMath::Sin(angle) * MovementAmplitude;
	SetActorLocation(SpawnPos + FVector(0, 0, verticalOffset));
}

void AShieldEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsValid(this))
	{
		GetWorldTimerManager().ClearAllTimersForObject(this);
	}

	for (AActor* Tentacle : SpawnedShieldTentacles)
	{
		Tentacle->Destroy();
	}
}