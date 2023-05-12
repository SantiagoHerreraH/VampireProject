// Fill out your copyright notice in the Description page of Project Settings.


#include "ProyectoVampiro/Widgets/ExperienceBar.h"

#include <string>

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UExperienceBar::SetExperienceBar(float CurrentXP, float MaxXP, int CurrentLevel)
{
	if(XPBar)
	{
		XPBar->SetPercent(CurrentXP/MaxXP);
	}

	if(Level)
	{
		Level->SetText(FText::AsNumber(CurrentLevel));
	}
}

void UExperienceBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!OwnerCharacter.IsValid())
		return;

	//XPBar->SetPercent(OwnerCharacter->);
}
