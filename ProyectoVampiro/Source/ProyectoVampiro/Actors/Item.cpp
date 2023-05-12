// Fill out your copyright notice in the Description page of Project Settings.


#include "ProyectoVampiro/Actors/Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Root of the object
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	this->StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	this->StaticMesh->SetupAttachment(RootComponent);

	this->BoxCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Box Collider"));
	this->BoxCollider->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

