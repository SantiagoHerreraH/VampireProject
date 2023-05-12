// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStats.generated.h"

enum ELevelUps
{
	MaxLife,
	LifeRestoredByItem,
	XPGained,
	Speed,
	PickUpRange,
	_GetRange
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROYECTOVAMPIRO_API UPlayerStats : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStats();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ------ STATS ------ //
	
	//-Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxLife = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float lifeRestoredByItem = 25.f;
	
	//-Experience
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float xPGained = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int maxLevel = 50.f;
	
	//-Movement & Enviroment
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float pickUpRange = 300.f;


	void LevelUpRandomStat();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// -------- LEVELING UP -------- //
	UFUNCTION(BlueprintCallable, Category = "Life")
	void LevelUp_MaxLife(float amount);
	UFUNCTION(BlueprintCallable, Category = "Life")
	void LevelUp_LifeRestoredByItem(float amount);

	UFUNCTION(BlueprintCallable, Category = "XP")
	void LevelUp_XPGained(float amount);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void LevelUp_Speed(float amount);
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void LevelUp_PickUpRange(float amount);

		
};
