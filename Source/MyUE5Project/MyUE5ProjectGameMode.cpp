// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyUE5ProjectGameMode.h"
#include "MyUE5ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyUE5ProjectGameMode::AMyUE5ProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
