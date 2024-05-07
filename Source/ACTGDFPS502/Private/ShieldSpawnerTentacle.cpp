// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldSpawnerTentacle.h"
#include "../EnemyBase.h"
#include "../WeakpointBase.h"
#include "NiagaraComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include <../ShieldEnemy.h>
#include "../../../../../5/5.3/UE_5.3/Engine/Source/Runtime/Engine/Classes/Components/ActorComponent.h"

void AShieldSpawnerTentacle::SetupShield()
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), Enemies);

	for (int i = 0; i < Enemies.Num(); i++)
	{
		AActor* Enemy = Enemies[i];

		if (UKismetMathLibrary::ClassIsChildOf(Enemy->GetClass(), AShieldEnemy::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("TENTACLE - Removed instance of Shield Spawner"));
			Enemies.RemoveAt(i);
		}
	}

	if (Enemies.IsEmpty() == false)
	{
		int EnemyArrayIndex = FMath::RandRange(0, Enemies.Num() - 1);
		EnemyReference = Cast<AEnemyBase>(Enemies[EnemyArrayIndex]);

		TArray<UWeakpointBase*> Weakpoints;
		EnemyReference->GetComponents(Weakpoints);

		if (Weakpoints.IsEmpty() == false)
		{
			int WeakpointArrayIndex = FMath::RandRange(0, Weakpoints.Num() - 1);
			WeakpointReference = Weakpoints[WeakpointArrayIndex]; 
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Weakpoint set."));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("TENTACLE - No Weakpoints attached to enemy. Destroying..."));
			Destroy();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TENTACLE - No Enemies. Destroying..."));
		Destroy();
	}

	if (IsValid(EnemyReference) && IsValid(WeakpointReference))
	{
		Spline->ClearSplinePoints();
		AddSplinePoints();
		CalculateSplinePoints();
		WeakpointReference->SetInvulnerability(true);
	}
	else
	{
		Destroy();
	}
}

// Sets default values
AShieldSpawnerTentacle::AShieldSpawnerTentacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(RootComponent);
	TentacleOrigin = CreateDefaultSubobject<USplineComponent>(TEXT("Tentacle Origin"));
	TentacleOrigin->SetupAttachment(RootComponent);
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));
	NiagaraComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AShieldSpawnerTentacle::BeginPlay()
{
	Super::BeginPlay();
}

void AShieldSpawnerTentacle::AddSplinePoints()
{
	for (int i = 0; i < NumberOfSplinePoints + 1; i++)
	{
		Spline->AddSplinePoint(FVector(0, 0, 0), ESplineCoordinateSpace::World);
	}
}

void AShieldSpawnerTentacle::CalculateSplinePoints()
{
	if (!IsValid(WeakpointReference) || !IsValid(TentacleOrigin))
	{
		Destroy();
		return;
	}

	StartingPoint = TentacleOrigin->GetComponentLocation();
	EnemyPoint = WeakpointReference->GetComponentLocation();
	BezierMiddlePoint = FMath::Lerp(StartingPoint, EnemyPoint, PercentageDistanceFromOriginForBezierMiddle/100);
	BezierMiddlePoint.Z = StartingPoint.Z - AmountToLowerBezierHeight;
	BezierMiddlePoint.Z = FMath::Clamp(BezierMiddlePoint.Z, 1050, 10000);

	for (int i = 0; i < NumberOfSplinePoints + 1; i++)
	{
		float CurveProgress = i / NumberOfSplinePoints;
		FVector FirstVector = FMath::Lerp(StartingPoint, BezierMiddlePoint, CurveProgress);
		FVector SecondVector = FMath::Lerp(BezierMiddlePoint, EnemyPoint, CurveProgress);
		FVector NewPoint = FMath::Lerp(FirstVector, SecondVector, CurveProgress);

		Spline->SetLocationAtSplinePoint(i, NewPoint, ESplineCoordinateSpace::World);
	}
}

// Called every frame
void AShieldSpawnerTentacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateSplinePoints();
	Spline->UpdateSpline();
}

void AShieldSpawnerTentacle::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsValid(WeakpointReference))
	{
		WeakpointReference->SetInvulnerability(false);
	}
}
