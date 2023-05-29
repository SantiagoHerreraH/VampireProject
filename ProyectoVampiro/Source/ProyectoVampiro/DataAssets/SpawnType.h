// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpawnType.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct FSpawnSpot {

	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<float> SpawnRadiuses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<float> SpawnDegreesFromCenterOnX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<float> SpawnDegreesFromCenterOnY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<float> SpawnDegreesFromCenterOnZ;
};

USTRUCT(BlueprintType)
struct FSpawnSpotIndexInfo {

	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentSpawnRadiusIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxSpawnRadiusIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentSpawnDegreesXIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxSpawnDegreesXIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentSpawnDegreesYIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxSpawnDegreesYIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentSpawnDegreesZIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxSpawnDegreesZIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator CurrentSpawnSpotRotation;

};

UCLASS()
class PROYECTOVAMPIRO_API USpawnType : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FSpawnSpot> SpawnSpots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<float> TimesForNextSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SpawnIsRelativeToActorRotation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxNumOfActorsToSpawn = 1;

};