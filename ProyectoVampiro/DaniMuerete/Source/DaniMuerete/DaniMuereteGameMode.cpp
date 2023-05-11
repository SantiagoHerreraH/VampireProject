// Copyright Epic Games, Inc. All Rights Reserved.

#include "DaniMuereteGameMode.h"
#include "DaniMuereteCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADaniMuereteGameMode::ADaniMuereteGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
