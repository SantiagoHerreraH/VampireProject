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
	this->m_currentLife = this->m_maxLife;
	// ...

}


// Called every frame
void ULifeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void ULifeComponent::ReduceLife(float amount)
{
	this->m_currentLife -= amount;
	if (this->m_currentLife <= 0.f) {
		//OnKillEntity.Execute();
	}
}

void ULifeComponent::RestoreLife(float amount)
{
	this->m_currentLife += amount;
	if (this->m_currentLife > this->m_maxLife) {
		this->m_currentLife = this->m_maxLife;
	}
}

void ULifeComponent::StartDamageOverTime(float dps)
{
	this->m_dps = dps;
	isDamageOverTime = true;
}

void ULifeComponent::StopDamageOverTime()
{
	isDamageOverTime = false;
}

