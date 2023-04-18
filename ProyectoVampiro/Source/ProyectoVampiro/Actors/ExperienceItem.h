// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProyectoVampiro/Actors/Item.h"
#include "ExperienceItem.generated.h"

/**
 * 
 */
UCLASS()
class PROYECTOVAMPIRO_API AExperienceItem : public AItem
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ExperienceGained;

	UFUNCTION(BlueprintCallable, Category = "ExperienceItem")
		void Init(float NewValue);
};
