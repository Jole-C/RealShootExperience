// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneEnemyShielded.h"
#include "Components/SphereComponent.h"

ADroneEnemyShielded::ADroneEnemyShielded()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADroneEnemyShielded::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		ShieldTimerHandle,
		this,
		&ADroneEnemyShielded::ToggleShieldState,
		ShieldCloseTimeSeconds,
		false
	);
}

void ADroneEnemyShielded::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearAllTimersForObject(this);
}

void ADroneEnemyShielded::ToggleShieldState()
{
	IsShieldOpen = !IsShieldOpen;

	float ChosenShieldTime = IsShieldOpen ? ShieldOpenTimeSeconds : ShieldCloseTimeSeconds;

	GetWorld()->GetTimerManager().SetTimer(
		ShieldTimerHandle,
		this,
		&ADroneEnemyShielded::ToggleShieldState,
		ChosenShieldTime,
		false
	);

}

