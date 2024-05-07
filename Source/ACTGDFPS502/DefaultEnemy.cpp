// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultEnemy.h"
#include <Kismet/KismetMathLibrary.h>
#include "Components/SphereComponent.h"

void ADefaultEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (ShouldRandomiseRotation == true)
	{
		SetActorRotation(UKismetMathLibrary::RandomRotator(false));
	}
}

ADefaultEnemy::ADefaultEnemy()
{
	PlayerDetectionRadius = CreateDefaultSubobject<USphereComponent>(TEXT("Player Detection Radius"));
	PlayerDetectionRadius->SetupAttachment(EntityMesh);

	EntityMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EntityMesh"));
	EntityWireframeBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EntityWireframeBase"));
	EntityMesh->SetupAttachment(RootEnemyComponent);
	EntityWireframeBase->SetupAttachment(EntityMesh);

	EntityMesh->SetCollisionProfileName(TEXT("EnemyBasis"));
	EntityWireframeBase->SetCollisionProfileName(TEXT("NoCollision"));
}