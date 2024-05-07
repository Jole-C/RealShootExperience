// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldWeakpoint.h"
#include "EnemyBase.h"

UShieldWeakpoint::UShieldWeakpoint()
{
	PrimaryComponentTick.bCanEverTick = true;
	ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield Mesh"));
	ShieldMesh->SetupAttachment(AttachmentPoint);
	ShieldMeshWireframe = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield Mesh Wireframe"));
	ShieldMeshWireframe->SetupAttachment(AttachmentPoint);
}

void UShieldWeakpoint::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		ShieldToggleTimerHandle,
		this,
		&UShieldWeakpoint::ToggleShield,
		ShieldToggleSeconds,
		true
	);
}

void UShieldWeakpoint::ToggleShield()
{
	isShielded = !isShielded;

	ShieldMesh->SetActive(isShielded);
	ShieldMesh->SetVisibility(isShielded);
	ShieldMeshWireframe->SetActive(isShielded);
	ShieldMeshWireframe->SetVisibility(isShielded);
}

void UShieldWeakpoint::OnWeakpointHit()
{
	if (Invulnerable)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Weakpoint is invulnerable."));
		return;
	}

	if (isShielded == true)
	{
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

void UShieldWeakpoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (IsValid(this))
	{
		GetWorld()->GetTimerManager().ClearTimer(ShieldToggleTimerHandle);
	}
}

void UShieldWeakpoint::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	CalculateLightIntensity();
}
