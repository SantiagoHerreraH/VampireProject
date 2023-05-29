// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Curves/CurveVector.h"

#include "MovementType.generated.h"




UCLASS()
class PROYECTOVAMPIRO_API UMovementType : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Behaviour Params")
		UCurveVector* Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Behaviour Params")
		float MovementDuration = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Behaviour Params")
		float MovementMultiplier = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Behaviour Params")
		TArray<FRotator> MovementDirections;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Behaviour Params")
		bool MovementDirectionFollowsOwner;

};
