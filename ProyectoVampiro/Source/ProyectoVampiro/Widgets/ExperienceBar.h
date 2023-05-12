// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExperienceBar.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROYECTOVAMPIRO_API UExperienceBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetExperienceBar(float CurrentXP,float MaxXP, int CurrentLevel);
	
protected:

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* XPBar;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Level;
	
};
