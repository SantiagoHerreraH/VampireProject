// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectileType.h"
#include "ProjectileGrowthType.generated.h"


/**
 *
 */
UCLASS()
class PROYECTOVAMPIRO_API UProjectileGrowthType : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<const UProjectileType*> ProjectileGrowthType;

	FORCEINLINE UProjectileGrowthType& operator=(const UProjectileGrowthType* const other) {

		ProjectileGrowthType.Empty();
		ProjectileGrowthType.Reserve(other->ProjectileGrowthType.Num());
		ProjectileGrowthType = other->ProjectileGrowthType;

		return *this;
	}

};
