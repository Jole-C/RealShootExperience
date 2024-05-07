// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ActorBase.generated.h"

UCLASS()
class ACTGDFPS502_API AActorBase : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	UStaticMeshComponent* EntityMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	UStaticMeshComponent* EntityWireframeBase;

public:	
	// Sets default values for this actor's properties
	AActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
