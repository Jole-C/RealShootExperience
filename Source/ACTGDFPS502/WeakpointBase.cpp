// Fill out your copyright notice in the Description page of Project Settings.


#include "WeakpointBase.h"
#include "EnemyBase.h"
#include "NiagaraFunctionLibrary.h"
#include "ACTGDFPS502Character.h"
#include "Camera/CameraComponent.h"
#include "Math/Vector.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>



UWeakpointBase::UWeakpointBase()
{
	PrimaryComponentTick.bCanEverTick = true;

	HitPoint = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	HitPoint->SetupAttachment(this);
	HitPoint->SetCollisionProfileName(TEXT("Weakpoint"));
	HitPoint->SetNotifyRigidBodyCollision(true);
	HitPoint->CanCharacterStepUpOn = ECB_No;

	DeathExplosionDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("DeathRotationDirection"));
	DeathExplosionDirection->SetupAttachment(this);

	Spotlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spotlight"));
	Spotlight->SetupAttachment(this);
	Spotlight->SetLightColor(FLinearColor(255, 0, 0, 1));
	Spotlight->SetRelativeLocation(FVector(156, 0, 0));
	Spotlight->SetIntensity(1000);
	Spotlight->SetIntensityUnits(ELightUnits::Lumens);
	Spotlight->SetVolumetricScatteringIntensity(10);
	Spotlight->SetInnerConeAngle(10);
	Spotlight->SetOuterConeAngle(20);
	Spotlight->SetAttenuationRadius(650);
	Spotlight->bUseTemperature = true;
	Spotlight->SetTemperature(100);
	
	EntityWireframeBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EntityWireframeBase"));
	EntityWireframeBase->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	EntityWireframeBase->SetCollisionProfileName(TEXT("NoCollision"));

	AttachmentPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Child Attachment Point"));
	AttachmentPoint->SetupAttachment(this);
}

void UWeakpointBase::BeginPlay()
{
	Super::BeginPlay();

	HitPoint->OnComponentBeginOverlap.AddDynamic(this, &UWeakpointBase::OnOverlapBegin);
	HitPoint->OnComponentHit.AddDynamic(this, &UWeakpointBase::OnHit);
	enemyReference = Cast<AEnemyBase>(GetOwner());
	WeakpointHealth = MaxWeakpointHealth;

	DefaultMaterial = (UMaterialInstance*)GetMaterial(0);
	SetMaterial(0, DefaultMaterial);

	CharacterReference = Cast<AACTGDFPS502Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void UWeakpointBase::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	CalculateLightIntensity();
}

void UWeakpointBase::ResetDamageMaterial()
{
	SetMaterial(0, DefaultMaterial);
}

void UWeakpointBase::CalculateLightIntensity()
{
}

void UWeakpointBase::OnWeakpointHit()
{
}

void UWeakpointBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(enemyReference == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Enemy is nullptr."));
		return;
	}

	OtherActor->Destroy();
	OnWeakpointHit();
}

void UWeakpointBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (enemyReference == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Enemy is nullptr."));
		return;
	}

	OnWeakpointHit();
}

void UWeakpointBase::SetDamageMaterialResetTimer()
{
	GetWorld()->GetTimerManager().SetTimer(
		DamageFlashMaterialTimerHandle,
		this,
		&UWeakpointBase::ResetDamageMaterial,
		HitFlashTimeSeconds,
		false
	);
}

void UWeakpointBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsValid(this))
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageFlashMaterialTimerHandle);
	}
}

void UWeakpointBase::CreateWeakpointDeathParticles()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathExplosionSystem, GetComponentLocation(), DeathExplosionDirection->GetComponentRotation(), FVector(1, 1, 1), true, true);
}
