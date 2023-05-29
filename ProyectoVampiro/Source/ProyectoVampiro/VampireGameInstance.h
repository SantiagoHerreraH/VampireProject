// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Actors/SpawnPool.h"

#include "VampireGameInstance.generated.h"

/**
 *
 */
UCLASS()
class PROYECTOVAMPIRO_API UVampireGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UVampireGameInstance();
	UFUNCTION(BlueprintCallable, Category = "SpawnPool")
		ASpawnPool* const GetSpawnPool();

private:
	UPROPERTY()
		ASpawnPool* SpawnPool;

};
