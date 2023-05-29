// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPool.h"

// Sets default values
ASpawnPool::ASpawnPool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnPoolComponent = CreateDefaultSubobject<USpawnComponent>(TEXT("SpawnPoolComponent"));
	SpawnPoolComponent->RegisterComponent();
	AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	AddInstanceComponent(SpawnPoolComponent);
}

// Called when the game starts or when spawned
void ASpawnPool::BeginPlay()
{
	Super::BeginPlay();
	initializeIfNotInitializedYet();
}

// Called every frame
void ASpawnPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

const bool ASpawnPool::DespawnActor(AActor* const actor, const TSubclassOf<AActor> classType)
{
	initializeIfNotInitializedYet();
	return SpawnPoolComponent->DespawnActor(actor, classType);
}

const bool ASpawnPool::SpawnActor(AActor* const actor, const TSubclassOf<AActor> classType, const FVector spawnLocation, const FRotator spawnedActorRotation, const FVector spawnedActorScale)
{
	initializeIfNotInitializedYet();
	return SpawnPoolComponent->SpawnActor(actor, classType, spawnLocation, spawnedActorRotation, spawnedActorScale);
}

const bool ASpawnPool::GetAllActorsOfClass_Map(const TSubclassOf<AActor> actorClassType, UPARAM(ref)TMap<AActor*, bool>& mapReference)
{
	initializeIfNotInitializedYet();
	return SpawnPoolComponent->GetAllActorsOfClass_Map(actorClassType, mapReference);
}

const bool ASpawnPool::GetActorsOfClass_Map(const TSubclassOf<AActor>& actorClassType, const int quantity_zero, UPARAM(ref)TMap<AActor*, bool>& mapReference)
{
	initializeIfNotInitializedYet();
	return SpawnPoolComponent->GetActorsOfClass_Map(actorClassType, quantity_zero, mapReference);
}

const bool ASpawnPool::GetAllActorsOfClass_Array(const TSubclassOf<AActor> type, UPARAM(ref)TArray<AActor*>& arrayRef)
{
	initializeIfNotInitializedYet();
	return SpawnPoolComponent->GetAllActorsOfClass_Array(type, arrayRef);
}

const bool ASpawnPool::GetActorsOfClass_Array(const TSubclassOf<AActor>& type, const int quantity_one, UPARAM(ref)TArray<AActor*>& arrayRef)
{
	initializeIfNotInitializedYet();
	return SpawnPoolComponent->GetActorsOfClass_Array(type, quantity_one, arrayRef);
}

TArray<AActor*>& ASpawnPool::GetArrayOfAllActorsOfClass(const TSubclassOf<AActor>& actorTypeArray)
{
	initializeIfNotInitializedYet();
	return SpawnPoolComponent->GetArrayOfAllActorsOfClass(actorTypeArray);
}

TMap<AActor*, bool>& ASpawnPool::GetMapOfAllActorsOfClass(const TSubclassOf<AActor>& actorTypeMap)
{
	initializeIfNotInitializedYet();
	return SpawnPoolComponent->GetMapOfAllActorsOfClass(actorTypeMap);
}

/*

	PRIVATE

*/

void ASpawnPool::initializeIfNotInitializedYet()
{
	if (!m_Initialized)
	{
		initialize();
	}
}

void ASpawnPool::initialize()
{
	m_Initialized = true;
	SpawnPoolComponent->ActorsToSpawnInfo = ActorsToSpawnInfo;
	SpawnPoolComponent->CreateAllActors();
}

