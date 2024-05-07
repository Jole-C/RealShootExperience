// Fill out your copyright notice in the Description page of Project Settings.


#include "BombEnemy.h"


ABombEnemy::ABombEnemy()
{
	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
	EnemyMesh->SetupAttachment(RootEnemyComponent);

	EnemyWireframeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Wireframe Mesh"));
	EnemyWireframeMesh->SetupAttachment(EnemyMesh);

	EnemyMesh->SetCollisionProfileName(TEXT("EnemyBasis"));
	EnemyWireframeMesh->SetCollisionProfileName(TEXT("NoCollision"));
}

void ABombEnemy::Explode_Implementation()
{
}