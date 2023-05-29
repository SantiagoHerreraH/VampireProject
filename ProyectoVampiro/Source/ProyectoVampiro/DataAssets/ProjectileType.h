// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "SpawnType.h"
#include "MovementType.h"

#include "ProjectileType.generated.h"

/**
 *
 */
UCLASS()
class PROYECTOVAMPIRO_API UProjectileType : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> ProjectileToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpawnType* SpawnType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMovementType* MovementType;

};
