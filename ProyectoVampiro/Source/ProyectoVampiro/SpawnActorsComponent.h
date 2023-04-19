// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnActorsComponent.generated.h"

UENUM()
enum Compass
{
	North		 UMETA(DisplayName = "North"),
	South		UMETA(DisplayName = "South"),
	East		UMETA(DisplayName = "East"),
	West		UMETA(DisplayName = "West"),
};

UCLASS()
class PROYECTOVAMPIRO_API ASpawnActorsComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnActorsComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY()
	TMap<TEnumAsByte<Compass>, float> SpawnRatios;

};
