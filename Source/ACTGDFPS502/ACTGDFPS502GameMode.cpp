// Copyright Epic Games, Inc. All Rights Reserved.

#include "ACTGDFPS502GameMode.h"
#include "ACTGDFPS502Character.h"
#include "UObject/ConstructorHelpers.h"

AACTGDFPS502GameMode::AACTGDFPS502GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
