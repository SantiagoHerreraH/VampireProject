// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnComponent.h"
#include "Math/Vector.h"

#include "../Actors/ProjectileController.h"

// Sets default values for this component's properties
USpawnComponent::USpawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	RegisterComponent();
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickEnabled(true);

	// ...
}

USpawnComponent::~USpawnComponent()
{

	if (!m_actorTypes.IsEmpty())
	{
		for (auto It = m_actorTypes.CreateIterator(); It; ++It)
		{
			for (auto ItMap = It->Value.ActorToSpawnStates.CreateIterator(); ItMap; ++ItMap)
			{

				if (ItMap->Key->IsValidLowLevelFast())
				{
					ItMap->Key->Destroy();
				}
			}

		}

		m_actorTypes.Empty();
	}

	if (!ActorsToSpawnInfo.IsEmpty())
	{
		ActorsToSpawnInfo.Empty();
	}
}

// Called when the game starts
void USpawnComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...

}


// Called every frame
void USpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...


}

const bool USpawnComponent::DespawnActor(AActor* const actor, const TSubclassOf<AActor> classType)
{
	createAllActorsIfNotCreatedYet();

	FSpawnedActorsGroup* actorState = m_actorTypes.Find(classType);
	if (actorState == nullptr)
	{
		return false;
	}

	bool* isActive = actorState->ActorToSpawnStates.Find(actor);

	if (isActive == nullptr)
	{
		return false;
	}
	if (!(*isActive))
	{
		return false;
	}

	*isActive = false;
	actor->SetActorEnableCollision(false);
	actor->SetActorHiddenInGame(true);
	actor->SetActorLocation(FVector(0, 0, 0));
	actor->SetActorRotation(FRotator(0, 0, 0));
	actor->SetActorScale3D(FVector(1, 1, 1));

	return true;
}

const bool USpawnComponent::SpawnActor(AActor* const actor, const TSubclassOf<AActor> classType, const FVector spawnLocation, const FRotator spawnedActorRotation, const FVector spawnedActorScale)
{
	createAllActorsIfNotCreatedYet();

	FSpawnedActorsGroup* actorState = m_actorTypes.Find(classType);
	if (actorState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - SpawnActor() - Couldn't find Static Class of Actor"));
		return false;
	}

	bool* isActive = actorState->ActorToSpawnStates.Find(actor);

	if (isActive == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - SpawnActor() - Couldn't find Actor perse"));
		return false;
	}
	if ((*isActive))
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - SpawnActor() - Actor is already Active"));
		return false;
	}

	*isActive = true;
	actor->SetActorLocation(spawnLocation);
	actor->SetActorRotation(spawnedActorRotation);
	actor->SetActorScale3D(spawnedActorScale);
	actor->SetActorEnableCollision(true);
	actor->SetActorHiddenInGame(false);

	return true;

}

/*
	Returns false if Actor Class Type doesn't exist
*/
const bool USpawnComponent::GetAllActorsOfClass_Map(const TSubclassOf<AActor>& actorClassType, UPARAM(ref)TMap<AActor*, bool>& mapReference)
{
	createAllActorsIfNotCreatedYet();

	FSpawnedActorsGroup* actorState = m_actorTypes.Find(actorClassType);
	if (actorState != nullptr && actorState->ActorToSpawnStates.Num() > 0)
	{
		if (!mapReference.IsEmpty())
		{
			mapReference.Empty();
		}

		mapReference.Reserve(actorState->ActorToSpawnStates.Num());
		mapReference = actorState->ActorToSpawnStates;

		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - GetAllActorsOfClass_Map() - Number of Projectiles TO SPAWN: %d"), actorState->ActorToSpawnStates.Num());

		return true;
	}
	if (actorState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - GetAllActorsOfClass_Map() - actorState is nullptr"));

		return false;
	}
	if (actorState->ActorArray.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - GetAllActorsOfClass_Map() -  Array size is : %d"), actorState->ActorToSpawnStates.Num());
	}

	return false;

}

const bool USpawnComponent::GetActorsOfClass_Map(const TSubclassOf<AActor>& actorClassType, const int quantity_zero, UPARAM(ref)TMap<AActor*, bool>& mapReference)
{
	createAllActorsIfNotCreatedYet();

	mapReference.Empty();

	unsigned int numOfActorsToGet;
	FSpawnedActorsGroup* actorState = m_actorTypes.Find(actorClassType);
	if (actorState != nullptr && actorState->ActorToSpawnStates.Num() > 0)
	{
		if (quantity_zero < actorState->ActorToSpawnStates.Num() && quantity_zero > 0)
		{
			numOfActorsToGet = quantity_zero;
		}
		else
		{
			numOfActorsToGet = actorState->ActorToSpawnStates.Num();
		}
		mapReference.Reserve(numOfActorsToGet);

		auto mapIt = actorState->ActorToSpawnStates.CreateIterator();
		//first deletes currently contained,and then copies
		for (size_t i = 0; i < numOfActorsToGet; i++)
		{
			mapReference.Emplace(mapIt->Key, mapIt->Value);
			++mapIt;
		}


		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - GetActorsOfClass_Map() - Number of Projectiles TO SPAWN: %d"), mapReference.Num());
		return true;
	}

	if (actorState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - GetActorsOfClass_Map() - actorState is nullptr"));

		return false;
	}
	if (actorState->ActorArray.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - GetActorsOfClass_Map() - Array size is : %d"), actorState->ActorToSpawnStates.Num());
	}

	return false;
}

/*
	Returns false if Actor Class Type doesn't exist
*/
const bool USpawnComponent::GetAllActorsOfClass_Array(const TSubclassOf<AActor>& type, UPARAM(ref)TArray<AActor*>& arrayRef)
{
	createAllActorsIfNotCreatedYet();

	FSpawnedActorsGroup* actorState = m_actorTypes.Find(type);
	if (actorState != nullptr && actorState->ActorArray.Num() > 0)
	{
		arrayRef.Reserve(actorState->ActorArray.Num());
		//first deletes currently contained,and then copies
		arrayRef = actorState->ActorArray;

		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - GetAllActorsOfClass_Array() - Number of Projectiles TO SPAWN: %d"), actorState->ActorArray.Num());
		return true;
	}
	if (actorState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - GetAllActorsOfClass_Array() - actorState is nullptr"));

		return false;
	}
	if (actorState->ActorArray.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - GetAllActorsOfClass_Array() - Array size is : %d"), actorState->ActorArray.Num());
	}

	return false;

}

const bool USpawnComponent::GetActorsOfClass_Array(const TSubclassOf<AActor>& type, const int quantity_one, UPARAM(ref)TArray<AActor*>& arrayRef)
{
	createAllActorsIfNotCreatedYet();

	arrayRef.Empty();

	unsigned int numOfActorsToGet;
	FSpawnedActorsGroup* actorState = m_actorTypes.Find(type);
	if (actorState != nullptr && actorState->ActorArray.Num() > 0)
	{
		if (quantity_one < actorState->ActorArray.Num() && quantity_one > 0)
		{
			numOfActorsToGet = quantity_one;
		}
		else
		{
			numOfActorsToGet = actorState->ActorArray.Num();
		}
		arrayRef.Reserve(numOfActorsToGet);

		//first deletes currently contained,and then copies
		for (size_t i = 0; i < numOfActorsToGet; i++)
		{
			arrayRef.Emplace(actorState->ActorArray[i]);
		}


		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - GetActorsOfClass_Array() - Number of Projectiles TO SPAWN: %d"), arrayRef.Num());
		return true;
	}

	if (actorState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - GetActorsOfClass_Array() -  actorState is nullptr"));

		return false;
	}
	if (actorState->ActorArray.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - GetActorsOfClass_Array() - Array size is : %d"), actorState->ActorArray.Num());
	}

	return false;

}

TArray<AActor*>& USpawnComponent::GetArrayOfAllActorsOfClass(const TSubclassOf<AActor>& actorTypeArray)
{
	createAllActorsIfNotCreatedYet();

	FSpawnedActorsGroup* actorState = m_actorTypes.Find(actorTypeArray);
	if (actorState != nullptr)
	{

		return actorState->ActorArray;
	}

	actorState = m_actorTypesRunTime.Find(actorTypeArray);

	if (actorState != nullptr)
	{
		return actorState->ActorArray;
	}

	createRunTimeCollection(actorTypeArray, m_defaultMemoryReserveForActors);
	actorState = m_actorTypesRunTime.Find(actorTypeArray);

	return actorState->ActorArray;
}

TMap<AActor*, bool>& USpawnComponent::GetMapOfAllActorsOfClass(const TSubclassOf<AActor>& actorTypeMap)
{
	createAllActorsIfNotCreatedYet();

	FSpawnedActorsGroup* actorState = m_actorTypes.Find(actorTypeMap);
	if (actorState != nullptr)
	{
		return actorState->ActorToSpawnStates;
	}

	actorState = m_actorTypesRunTime.Find(actorTypeMap);

	if (actorState != nullptr)
	{
		return actorState->ActorToSpawnStates;
	}

	createRunTimeCollection(actorTypeMap, m_defaultMemoryReserveForActors);
	actorState = m_actorTypesRunTime.Find(actorTypeMap);

	return actorState->ActorToSpawnStates;
}
/*
	Return false if characters already created;
*/
const bool USpawnComponent::CreateAllActors() {

	return createAllActorsIfNotCreatedYet();
}


/*

	PRIVATE

*/

const bool USpawnComponent::createAllActorsIfNotCreatedYet()
{
	if (m_numberOfTimesCreatedAllActors == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - Creating Actors"));
		createAllActors();
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - Actors Already Created"));
	return false;
}
void USpawnComponent::createAllActors()
{
	m_numberOfTimesCreatedAllActors++;
	//How does reserving memory of a class that has collection types actually work?
	m_actorTypes.Reserve(ActorsToSpawnInfo.Num());
	reserveSpaceForRunTimeCollection();

	FActorSpawnParameters spawnParams;
	FVector ownerActorLocation = FVector(0, 0, 0);
	FRotator ownerActorRotation = FRotator(0, 0, 0);

	//Create
	for (size_t i = 0; i < ActorsToSpawnInfo.Num(); i++)
	{
		FSpawnedActorsGroup newSpawnGroup;
		newSpawnGroup.ActorArray.Reserve(ActorsToSpawnInfo[i].NumberOfActorsToSpawn);
		newSpawnGroup.ActorToSpawnStates.Reserve(ActorsToSpawnInfo[i].NumberOfActorsToSpawn);

		for (size_t j = 0; j < ActorsToSpawnInfo[i].NumberOfActorsToSpawn; j++)
		{
			AActor* newActorCreated = GetWorld()->SpawnActor(
				ActorsToSpawnInfo[i].ActorToSpawn,
				&ownerActorLocation,
				&ownerActorRotation,
				spawnParams);

			newActorCreated->SetActorEnableCollision(false);
			newActorCreated->SetActorHiddenInGame(true);

			newSpawnGroup.ActorToSpawnStates.Emplace(
				&*newActorCreated, false);

			newSpawnGroup.ActorArray.Emplace(&*newActorCreated);

			//QUESTION: How to override FSpawnedActorsGroup constructor so that,
			//when a copy is made, you reserve space before emplacing the new values so that the pointer references are not lost
		}

		m_actorTypes.Emplace(ActorsToSpawnInfo[i].ActorToSpawn, newSpawnGroup);

		const bool checkClassType = ActorsToSpawnInfo[i].ActorToSpawn == AProjectileController::StaticClass();
		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - createAllActors() - Type of actor spawned is AProjectileController?:  %s"), checkClassType ? TEXT("TRUE") : TEXT("FALSE"));
		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - createAllActors() - Number of Projectiles TO SPAWN IN ARRAY: %d"), newSpawnGroup.ActorArray.Num());
		UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - createAllActors() - Number of Projectiles TO SPAWN IN MAP: %d"), newSpawnGroup.ActorToSpawnStates.Num());
	}

	UE_LOG(LogTemp, Warning, TEXT("SpawnComponent - createAllActors() - Actors To Spawn Info Num: %d"), ActorsToSpawnInfo.Num());

}
void USpawnComponent::reserveSpaceForRunTimeCollection() {

	m_actorTypesRunTime.Reserve(m_defaultMemoryReserveForTypes);
}

void USpawnComponent::createRunTimeCollection(const TSubclassOf<AActor>& actorClassType, const int numberOfActorsToCreate) {

	m_actorTypesRunTime.Reserve(numberOfActorsToCreate);

	FActorSpawnParameters spawnParams;
	FVector ownerActorLocation = FVector(0, 0, 0);
	FRotator ownerActorRotation = FRotator(0, 0, 0);


	FSpawnedActorsGroup newSpawnGroup;
	newSpawnGroup.ActorArray.Reserve(numberOfActorsToCreate);
	newSpawnGroup.ActorToSpawnStates.Reserve(numberOfActorsToCreate);

	for (size_t j = 0; j < numberOfActorsToCreate; j++)
	{
		AActor* newActorCreated = GetWorld()->SpawnActor(
			actorClassType,
			&ownerActorLocation,
			&ownerActorRotation,
			spawnParams);

		newActorCreated->SetActorEnableCollision(false);
		newActorCreated->SetActorHiddenInGame(true);

		newSpawnGroup.ActorToSpawnStates.Emplace(
			&*newActorCreated, false);

		newSpawnGroup.ActorArray.Emplace(&*newActorCreated);
	}



	m_actorTypesRunTime.Emplace(actorClassType, newSpawnGroup);


}