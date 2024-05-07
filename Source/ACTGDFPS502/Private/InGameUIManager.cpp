// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUIManager.h"

// Sets default values
AInGameUIManager::AInGameUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInGameUIManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInGameUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

