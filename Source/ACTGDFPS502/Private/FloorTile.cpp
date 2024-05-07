// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTile.h"
#include "Components/SphereComponent.h"

// Sets default values
AFloorTile::AFloorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(PlayerDetection);

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	FloorMesh->SetupAttachment(PlayerDetection);
}

// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
