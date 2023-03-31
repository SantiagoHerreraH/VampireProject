// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProyectoVampiroGameMode.h"
#include "ProyectoVampiroCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProyectoVampiroGameMode::AProyectoVampiroGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
