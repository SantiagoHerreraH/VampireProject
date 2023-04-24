// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProyectoVampiro/Components/LifeComponent.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LifeBar.generated.h"

/**
 * 
 */
UCLASS( Abstract )
class PROYECTOVAMPIRO_API ULifeBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* LifeBar;
	/*UProperty(VisibleAnywhere)
		ULifeComponent* LifeComponent = nullptr;*/
};
