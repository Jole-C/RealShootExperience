// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySplitter.h"
#include "Components/SceneComponent.h"

AEnemySplitter::AEnemySplitter()
{
	SplitterMeshRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Splitter Segment Root"));
	SplitterMeshRoot->SetupAttachment(RootComponent);
	SplitterSegmentLower = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Splitter Segment Lower"));
	SplitterSegmentLower->SetupAttachment(SplitterMeshRoot);
	SplitterSegmentUpper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Splitter Segment Upper"));
	SplitterSegmentUpper->SetupAttachment(SplitterMeshRoot);

	SplitterSegmentLowerWireframe = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Splitter Segment Lower Wireframe"));
	SplitterSegmentLowerWireframe->SetupAttachment(SplitterMeshRoot);
	SplitterSegmentUpperWireframe = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Splitter Segment Upper Wireframe"));
	SplitterSegmentUpperWireframe->SetupAttachment(SplitterMeshRoot);
}
