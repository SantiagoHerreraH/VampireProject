// Fill out your copyright notice in the Description page of Project Settings.

#include "ProyectoVampiro/Components/LifeComponent.h"


// Sets default values for this component's properties
ULifeComponent::ULifeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void ULifeComponent::BeginPlay()
{
	Super::BeginPlay();
	//maxLife=_PlayerStats->maxLife;
	this->currentLife = this->maxLife;
	// ...
	
}


// Called every frame
void ULifeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//maxLife=_PlayerStats->maxLife;
}



void ULifeComponent::ReduceLife(float amount)
{
	this->currentLife -= amount;
	if (this->currentLife <= 0.f) {
		this->currentLife = 0.f;
		this->OnKillEntity.Execute();
	}
	UE_LOG(LogTemp, Warning, TEXT("Current life: %f"), this->currentLife);
}

void ULifeComponent::RestoreLife(float amount)
{
	this->currentLife += amount;

	if (this->currentLife > this->maxLife) {
		this->currentLife = this->maxLife;
	}

	UE_LOG(LogTemp, Warning, TEXT("Current life: %f"), this->currentLife);
}

void ULifeComponent::StartDamageOverTime(float damage, float time)
{
	this->damagePerTick = damage;
	this->timeBetweenTicks = time;
	isDamageOverTime = true;
}

void ULifeComponent::StopDamageOverTime()
{
	isDamageOverTime = false;
}

