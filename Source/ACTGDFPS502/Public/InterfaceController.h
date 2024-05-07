// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterfaceController.generated.h"

UCLASS()
class ACTGDFPS502_API AInterfaceController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInterfaceController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
