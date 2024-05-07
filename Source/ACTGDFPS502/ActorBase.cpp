// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorBase.h"

AActorBase::AActorBase()
{
	PrimaryActorTick.bCanEverTick = true;

	EntityMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EntityMesh"));
	SetRootComponent(EntityMesh);

	EntityWireframeBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EntityWireframeBase"));
	EntityWireframeBase->SetupAttachment(EntityMesh);

	EntityMesh->SetCollisionProfileName(TEXT("EnemyBasis"));
	EntityWireframeBase->SetCollisionProfileName(TEXT("NoCollision"));
}

void AActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

