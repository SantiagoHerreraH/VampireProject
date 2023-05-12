// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProyectoVampiro/Actors/Item.h"
#include "FirstAidKitItem.generated.h"

/**
 * 
 */
UCLASS()
class PROYECTOVAMPIRO_API AFirstAidKitItem : public AItem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LifeRecovered{};

	UFUNCTION(BlueprintCallable, Category = "First Aid Kit Item")
		void Init(float NewValue);
};
