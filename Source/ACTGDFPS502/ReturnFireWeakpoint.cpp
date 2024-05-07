// Fill out your copyright notice in the Description page of Project Settings.


#include "ReturnFireWeakpoint.h"
#include "EnemyBase.h"
#include "ACTGDFPS502Character.h"
#include "ACTGDFPS502Projectile.h"
#include "TimerManager.h"

UReturnFireWeakpoint::UReturnFireWeakpoint()
{
	PrimaryComponentTick.bCanEverTick = true;

	ProjectileFireLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Fire Location"));
	ProjectileFireLocation->SetupAttachment(AttachmentPoint);
	ProjectileFireLocation->SetRelativeLocation(FVector(130, 0, 0));
}

void UReturnFireWeakpoint::OnWeakpointHit()
{
	if (Invulnerable)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Weakpoint is invulnerable."));
		return;
	}

	currentNumberOfBulletsToFire = NumberOfBulletsToFire;

	SetMaterial(0, HitMaterial);
	SetDamageMaterialResetTimer();		

	if (WeakpointHealth > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(
			FireTimerHandle,
			this,
			&UReturnFireWeakpoint::FireProjectile,
			ReturnFireCooldownSeconds,
			false
		);
	}

	WeakpointHealth -= 1;
}

void UReturnFireWeakpoint::FireProjectile()
{
	const FRotator SpawnRotation = (CharacterReference->GetActorLocation() - GetComponentLocation()).Rotation();
	AACTGDFPS502Projectile* projectile = GetWorld()->SpawnActor<AACTGDFPS502Projectile>(ProjectileClass, ProjectileFireLocation->GetComponentLocation(), SpawnRotation);

	if (currentNumberOfBulletsToFire > 0)
	{
		currentNumberOfBulletsToFire -= 1;	
		
		GetWorld()->GetTimerManager().SetTimer(
			FireTimerHandle,
			this,
			&UReturnFireWeakpoint::FireProjectile,
			ReturnFireCooldownSeconds,
			false
		);
	}

	if (WeakpointHealth <= 0)
	{
		CreateWeakpointDeathParticles();
		enemyReference->DamageEnemy(1);
		DestroyComponent();
	}
}

void UReturnFireWeakpoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (IsValid(this))
	{
		GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	}
}

void UReturnFireWeakpoint::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	CalculateLightIntensity();
}