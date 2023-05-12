// Fill out your copyright notice in the Description page of Project Settings.


#include "ProyectoVampiro/Components/PlayerStats.h"

// Sets default values for this component's properties
UPlayerStats::UPlayerStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UPlayerStats::LevelUpRandomStat()
{
	int Rand =FMath::RandRange(0, ELevelUps::_GetRange - 1);
	int test=0;
	switch (test)
	{
	case 0:
		LevelUp_MaxLife(15.f);
		GEngine->AddOnScreenDebugMessage(0,2.f,FColor::Green,FString::Printf(TEXT("Max Life leveled up! Curren MaxLife: %f"), maxLife));
		break;
	case 1:
		LevelUp_LifeRestoredByItem(10.f);
		GEngine->AddOnScreenDebugMessage(0,2.f,FColor::Green,"Life Restored By Items leveled up!");
		break;
	case 2:
		LevelUp_XPGained(10.f);
		GEngine->AddOnScreenDebugMessage(0,2.f,FColor::Green,"XP Gained leveled up!");
		break;
	case 3:
		LevelUp_Speed(75.f);
		GEngine->AddOnScreenDebugMessage(0,2.f,FColor::Green,"Speed leveled up!");
		break;
	case 4:
		LevelUp_PickUpRange(100.f);
		GEngine->AddOnScreenDebugMessage(0,2.f,FColor::Green,"PickUpRange leveled up!");
	}
}

// Called when the game starts
void UPlayerStats::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UPlayerStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//------- LEVELING UP -------//

void UPlayerStats::LevelUp_MaxLife(float amount)
{
	maxLife+=amount;
}

void UPlayerStats::LevelUp_LifeRestoredByItem(float amount)
{
	lifeRestoredByItem+=amount;
}

void UPlayerStats::LevelUp_XPGained(float amount)
{
	xPGained+=amount;
}

void UPlayerStats::LevelUp_Speed(float amount)
{
	speed+=amount;
}

void UPlayerStats::LevelUp_PickUpRange(float amount)
{
	pickUpRange+=amount;
}



