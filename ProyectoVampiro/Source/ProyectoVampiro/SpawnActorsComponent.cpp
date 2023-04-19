// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnActorsComponent.h"

// Sets default values
ASpawnActorsComponent::ASpawnActorsComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnActorsComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnActorsComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

