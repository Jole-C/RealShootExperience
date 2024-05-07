// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultWeakpoint.h"
#include "EnemyBase.h"

UDefaultWeakpoint::UDefaultWeakpoint()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDefaultWeakpoint::OnWeakpointHit()
{
	if (Invulnerable)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Weakpoint is invulnerable."));
		return;
	}

	SetMaterial(0, HitMaterial);
	SetDamageMaterialResetTimer();

	WeakpointHealth -= 1;

	if (WeakpointHealth <= 0)
	{
		CreateWeakpointDeathParticles();
		enemyReference->DamageEnemy(1);
		DestroyComponent();
	}
}

void UDefaultWeakpoint::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	CalculateLightIntensity();
}