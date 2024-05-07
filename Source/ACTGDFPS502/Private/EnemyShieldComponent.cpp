// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyShieldComponent.h"
#include "../EnemyBase.h"
#include "../WeakpointBase.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetArrayLibrary.h>

// Sets default values for this component's properties
UEnemyShieldComponent::UEnemyShieldComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(this);
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));
	NiagaraComponent->SetupAttachment(this);
}


// Called when the game starts
void UEnemyShieldComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UEnemyShieldComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsValid(WeakpointReference) && IsValid(EnemyReference))
	{
		StartingPoint.Position = GetComponentLocation();
		EnemyPoint.Position = WeakpointReference->GetComponentLocation();
		DrawDebugSphere(GetWorld(), StartingPoint.Position, 30, 32, FColor::Purple, false, 0, 0U, 10);
		DrawDebugSphere(GetWorld(), EnemyPoint.Position, 30, 32, FColor::Green, false, 0, 0U, 10);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Weakpoint or Enemy reference are no longer valid."));
	}

	// ...
}

void UEnemyShieldComponent::SetupShield()
{
}

