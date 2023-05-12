// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProyectoVampiro/ProyectoVampiroCharacter.h"

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
	void SetOwnerCharacter(AProyectoVampiroCharacter* InCharacter) { OwnerCharacter = InCharacter; }
	void SetExperienceBar(float CurrentXP,float MaxXP, int CurrentLevel);
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime)override;

	TWeakObjectPtr<AProyectoVampiroCharacter> OwnerCharacter;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* XPBar;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Level;
	
};
