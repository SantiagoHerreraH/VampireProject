// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpawnComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "../VampireGameInstance.h"

// Sets default values for this component's properties
UProjectileSpawnComponent::UProjectileSpawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	RegisterComponent();
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickEnabled(true);

	// ...
}

UProjectileSpawnComponent::~UProjectileSpawnComponent()
{

}

// Called when the game starts
void UProjectileSpawnComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...

}


// Called every frame
void UProjectileSpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...


}

AActor* const UProjectileSpawnComponent::Spawn()
{

	if (m_Initialized)
	{
		spawnOnTime();

		if (m_actorsSpawned.Num() > 0)
		{
			return m_actorsSpawned[m_currentSpawnActorIndex];
		}

	}

	UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - GetSpawnedActors() - SetSpawnParametersBeforeGettingSpawnedActors"));


	return nullptr;
}
TArray<AActor*>& UProjectileSpawnComponent::GetSpawnedActors()
{
	if (!m_Initialized)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - GetSpawnedActors() - SetSpawnParametersBeforeGettingSpawnedActors"));
	}

	return m_actorsSpawned;
}
const bool UProjectileSpawnComponent::SetSpawnType(USpawnType* const spawnTypePtr)
{
	if (m_Initialized)
	{
		if (spawnTypePtr != nullptr)
		{
			emptySpawnSpots();
			SpawnType = spawnTypePtr;
			initialize();
			return true;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - GetSpawnedActors() - SetSpawnParametersBeforeGettingSpawnedActors"));

	return false;
}
const bool UProjectileSpawnComponent::SetSpawnParameters(USpawnType* const spawnType, const TSubclassOf<AActor> actorType)
{
	if (spawnType != nullptr)
	{
		m_Initialized = true;
		ActorToSpawn = actorType;
		emptySpawnSpots();
		SpawnType = spawnType;
		initialize();
		return true;
	}
	return false;
}
/*

	PRIVATE

*/

void UProjectileSpawnComponent::initialize()
{
	//order matters (last one always last)
	setDefaultActor();
	getActorRefsFromSpawnPool();
	createdefaultActorRefs();

	setSpawnSpots();
	setSpawnSpotsInfo();
	setTimes();
	setSpawnLocation();
	setSpawnActorIndexes();

	//printResults();
}

void UProjectileSpawnComponent::setDefaultActor()
{
	if (ActorToSpawn == nullptr)
	{
		ActorToSpawn = AActor::StaticClass();
	}
}


void UProjectileSpawnComponent::getActorRefsFromSpawnPool()
{
	if (SpawnType != nullptr)
	{
		MaxNumOfActorsToSpawn = SpawnType->MaxNumOfActorsToSpawn;
	}

	if (GetWorld() != nullptr)
	{
		UGameInstance* nonCastedGameInstance = UGameplayStatics::GetGameInstance(GetWorld());

		UVampireGameInstance* gameInstance = nullptr;
		ASpawnPool* spawnPool = nullptr;

		if (nonCastedGameInstance != nullptr)
		{
			gameInstance = Cast<UVampireGameInstance>(nonCastedGameInstance);
		}
		if (gameInstance != nullptr)
		{
			spawnPool = gameInstance->GetSpawnPool();
		}
		if (spawnPool != nullptr)
		{
			spawnPool->GetActorsOfClass_Array(ActorToSpawn, MaxNumOfActorsToSpawn, m_actorsSpawned);
			UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - getActorRefsFromSpawnPool() - Number of SPAWNED Projectiles: %d"), m_actorsSpawned.Num());
		}


		if (spawnPool == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - getActorRefsFromSpawnPool() - SpawnPool is nullptr"));
		}
		if (gameInstance == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - getActorRefsFromSpawnPool() - GameInstance is nullptr"));

		}
		if (nonCastedGameInstance == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - getActorRefsFromSpawnPool() - GameInstance is nullptr"));
		}
	}

	if (GetWorld() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - getActorRefsFromSpawnPool() - GetWorld is nullptr"));
	}
}


void UProjectileSpawnComponent::createdefaultActorRefs()
{

	if (m_actorsSpawned.Num() == 0)
	{
		setActors();
	}
}

void UProjectileSpawnComponent::setActors()
{

	if (GetOwner() != nullptr && GetWorld() != nullptr)
	{
		FActorSpawnParameters spawnParams;
		FVector ownerActorLocation = GetOwner()->GetActorLocation();
		FRotator ownerActorRotation = GetOwner()->GetActorRotation();
		m_actorsSpawned.Reserve(MaxNumOfActorsToSpawn);

		for (size_t i = 0; i < MaxNumOfActorsToSpawn; i++)
		{
			m_actorsSpawned.Emplace(
				GetWorld()->SpawnActor(
					ActorToSpawn,
					&ownerActorLocation,
					&ownerActorRotation,
					spawnParams));
			m_actorsSpawned[i]->SetActorEnableCollision(false);
			m_actorsSpawned[i]->SetActorHiddenInGame(true);
		}
	}

}

void UProjectileSpawnComponent::setSpawnSpots()
{
	//Check if every necessarry variable was filled
	//If not, default it
	if (SpawnSpots.Num() <= 0 && SpawnType == nullptr)
	{
		createDefaultSpawnSpot();
	}
	else if (SpawnType != nullptr)
	{
		emptyUnnecessarySpawnSpots();
		createSpawnSpotsOutOfSpawnType();
		SpawnIsRelativeToActorRotation = SpawnType->SpawnIsRelativeToActorRotation;
	}
	else
	{
		fillDefaultSpawnSpots();
	}
}

void UProjectileSpawnComponent::emptyUnnecessarySpawnSpots()
{
	for (size_t i = 0; i < SpawnSpots.Num(); i++)
	{
		SpawnSpots[i].SpawnDegreesFromCenterOnX.Empty();
		SpawnSpots[i].SpawnDegreesFromCenterOnY.Empty();
		SpawnSpots[i].SpawnDegreesFromCenterOnZ.Empty();
		SpawnSpots[i].SpawnRadiuses.Empty();
	}

	SpawnSpots.Empty();
}

void UProjectileSpawnComponent::createSpawnSpotsOutOfSpawnType()
{
	for (size_t i = 0; i < SpawnType->SpawnSpots.Num(); i++)
	{
		SpawnSpots.Emplace(FSpawnSpot());

		if (SpawnType->SpawnSpots[i].SpawnRadiuses.Num() == 0)
		{
			SpawnSpots[i].SpawnRadiuses.Emplace(100);
		}
		else
		{
			for (size_t j = 0; j < SpawnType->SpawnSpots[i].SpawnRadiuses.Num(); j++)
			{
				SpawnSpots[i].SpawnRadiuses.Emplace(SpawnType->SpawnSpots[i].SpawnRadiuses[j]);
			}

		}

		if (SpawnType->SpawnSpots[i].SpawnDegreesFromCenterOnX.Num() == 0)
		{
			SpawnSpots[i].SpawnDegreesFromCenterOnX.Emplace(0);

		}
		else
		{
			for (size_t j = 0; j < SpawnType->SpawnSpots[i].SpawnDegreesFromCenterOnX.Num(); j++)
			{
				SpawnSpots[i].SpawnDegreesFromCenterOnX.Emplace(SpawnType->SpawnSpots[i].SpawnDegreesFromCenterOnX[j]);
			}

		}

		if (SpawnType->SpawnSpots[i].SpawnDegreesFromCenterOnY.Num() == 0)
		{
			SpawnSpots[i].SpawnDegreesFromCenterOnY.Emplace(0);
		}
		else
		{
			for (size_t j = 0; j < SpawnType->SpawnSpots[i].SpawnDegreesFromCenterOnY.Num(); j++)
			{
				SpawnSpots[i].SpawnDegreesFromCenterOnY.Emplace(SpawnType->SpawnSpots[i].SpawnDegreesFromCenterOnY[j]);
			}
		}

		if (SpawnType->SpawnSpots[i].SpawnDegreesFromCenterOnZ.Num() == 0)
		{
			SpawnSpots[i].SpawnDegreesFromCenterOnZ.Emplace(0);
		}
		else
		{
			for (size_t j = 0; j < SpawnType->SpawnSpots[i].SpawnDegreesFromCenterOnZ.Num(); j++)
			{
				SpawnSpots[i].SpawnDegreesFromCenterOnZ.Emplace(SpawnType->SpawnSpots[i].SpawnDegreesFromCenterOnZ[j]);
			}
		}
	}
}

void UProjectileSpawnComponent::fillDefaultSpawnSpots()
{
	for (size_t i = 0; i < SpawnSpots.Num(); i++)
	{
		if (SpawnSpots[i].SpawnRadiuses.Num() == 0)
		{
			SpawnSpots[i].SpawnRadiuses.Emplace(100);
		}

		if (SpawnSpots[i].SpawnDegreesFromCenterOnX.Num() == 0)
		{
			SpawnSpots[i].SpawnDegreesFromCenterOnX.Emplace(0);
		}

		if (SpawnSpots[i].SpawnDegreesFromCenterOnY.Num() == 0)
		{
			SpawnSpots[i].SpawnDegreesFromCenterOnY.Emplace(0);
		}

		if (SpawnSpots[i].SpawnDegreesFromCenterOnZ.Num() == 0)
		{
			SpawnSpots[i].SpawnDegreesFromCenterOnZ.Emplace(0);
		}
	}
}

void UProjectileSpawnComponent::createDefaultSpawnSpot()
{
	SpawnSpots.Emplace(FSpawnSpot());
	SpawnSpots[0].SpawnRadiuses.Emplace(100);
	SpawnSpots[0].SpawnDegreesFromCenterOnX.Emplace(0);
	SpawnSpots[0].SpawnDegreesFromCenterOnY.Emplace(0);
	SpawnSpots[0].SpawnDegreesFromCenterOnZ.Emplace(0);
}

void UProjectileSpawnComponent::setTimes()
{
	if ((SpawnType == nullptr &&
		TimesForNextSpawn.IsEmpty()) ||

		(TimesForNextSpawn.Num() == 0 &&
			(SpawnType != nullptr && SpawnType->TimesForNextSpawn.Num() == 0)))
	{
		createDefaultTimes();
	}
	else if (SpawnType != nullptr && SpawnType->TimesForNextSpawn.Num() > 0)
	{
		if (!TimesForNextSpawn.IsEmpty())
		{
			TimesForNextSpawn.Empty();
		}

		for (size_t i = 0; i < SpawnType->TimesForNextSpawn.Num(); i++)
		{
			TimesForNextSpawn.Emplace(SpawnType->TimesForNextSpawn[i]);
		}
	}
	else
	{
		createDefaultTimes();
	}
}

void UProjectileSpawnComponent::createDefaultTimes()
{
	TimesForNextSpawn.Empty();
	TimesForNextSpawn.Emplace(1);
}

void UProjectileSpawnComponent::setSpawnSpotsInfo()
{
	m_spawnSpotsIndexInfo.Empty();

	for (size_t i = 0; i < SpawnSpots.Num(); i++)
	{
		m_spawnSpotsIndexInfo.Emplace(FSpawnSpotIndexInfo());

		m_spawnSpotsIndexInfo[i].CurrentSpawnRadiusIndex = 0;
		m_spawnSpotsIndexInfo[i].MaxSpawnRadiusIndex =
			SpawnSpots[i].SpawnRadiuses.Num() - 1 > 0 ?
			SpawnSpots[i].SpawnRadiuses.Num() - 1 : 0;

		m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesXIndex = 0;
		m_spawnSpotsIndexInfo[i].MaxSpawnDegreesXIndex =
			SpawnSpots[i].SpawnDegreesFromCenterOnX.Num() - 1 > 0 ?
			SpawnSpots[i].SpawnDegreesFromCenterOnX.Num() - 1 : 0;

		m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesYIndex = 0;
		m_spawnSpotsIndexInfo[i].MaxSpawnDegreesYIndex =
			SpawnSpots[i].SpawnDegreesFromCenterOnY.Num() - 1 > 0 ?
			SpawnSpots[i].SpawnDegreesFromCenterOnY.Num() - 1 : 0;

		m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesZIndex = 0;
		m_spawnSpotsIndexInfo[i].MaxSpawnDegreesZIndex =
			SpawnSpots[i].SpawnDegreesFromCenterOnZ.Num() - 1 > 0 ?
			SpawnSpots[i].SpawnDegreesFromCenterOnZ.Num() - 1 : 0;

		m_spawnSpotsIndexInfo[i].CurrentSpawnSpotRotation = FRotator(0, 0, 0);
	}
}

void UProjectileSpawnComponent::setSpawnLocation()
{
	if (GetOwner() != nullptr)
	{
		m_spawnLocation = GetOwner()->GetActorLocation();
	}
}

void UProjectileSpawnComponent::setSpawnActorIndexes()
{
	m_currentSpawnActorIndex = 0;
	m_maxSpawnActorIndex = m_actorsSpawned.Num() > 0 ? m_actorsSpawned.Num() - 1 : 0;

	m_currentSpawnSpotIndex = 0;
	m_maxSpawnSpotIndex = SpawnSpots.Num() > 0 ? SpawnSpots.Num() - 1 : 0;

	m_currentTimeIndex = 0;
	m_maxTimeIndex = TimesForNextSpawn.Num() > 0 ? TimesForNextSpawn.Num() - 1 : 0;

	m_currentTimeSinceSpawned = 0;
	m_maxTimeSinceSpawned = TimesForNextSpawn.Num() > 0 ? TimesForNextSpawn[m_currentTimeIndex] : 1;
}

void UProjectileSpawnComponent::printResults()
{

	UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - printResults() - MaxNumOfActorsToSpawn: %d"), MaxNumOfActorsToSpawn);

	//SpawnSpots
	UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - printResults() - SPAWN SPOTS"));
	for (size_t i = 0; i < SpawnSpots.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - printResults() - SPAWN SPOT INDEX: %d"), i);


		UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - printResults() - SPAWN RADIUS"));
		for (size_t j = 0; j < SpawnSpots[i].SpawnRadiuses.Num(); j++)
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - printResults() - SpawnRadiusNumber: %d"), j);
			UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - printResults() - CurrentSpawnRadiusValue: %f"), SpawnSpots[i].SpawnRadiuses[j]);

		}
		UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponennt - printResults() - SPAWN DEGREES X"));
		for (size_t j = 0; j < SpawnSpots[i].SpawnDegreesFromCenterOnX.Num(); j++)
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - printResults() - SpawnDegreesFromCenterOnX: %d"), j);
			UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - printResults() - CurrentSpawnRadiusValue: %f"), SpawnSpots[i].SpawnDegreesFromCenterOnX[j]);

		}
		UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - printResults() - SPAWN DEGREES Y"));
		for (size_t j = 0; j < SpawnSpots[i].SpawnDegreesFromCenterOnY.Num(); j++)
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - printResults() - SpawnDegreesFromCenterOnY: %d"), j);
			UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - printResults() - CurrentSpawnRadiusValue: %f"), SpawnSpots[i].SpawnDegreesFromCenterOnY[j]);

		}
		UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponennt - printResults() - SPAWN DEGREES Z"));
		for (size_t j = 0; j < SpawnSpots[i].SpawnDegreesFromCenterOnZ.Num(); j++)
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - printResults() - SpawnDegreesFromCenterOnZ: %d"), j);
			UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - printResults() - CurrentSpawnRadiusValue: %f"), SpawnSpots[i].SpawnDegreesFromCenterOnZ[j]);

		}
	}
	UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponennt - printResults() - SPAWN TIMES"));
	for (size_t i = 0; i < TimesForNextSpawn.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponennt - printResults() - TimesForNextSpawnNumber: %d"), i);
		UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponennt - printResults() - TimesForNextSpawnValue: %f"), TimesForNextSpawn[i]);

	}
	UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponennt - printResults() - IS RELATIVE"));
	UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponennt - printResults() - SpawnIsRelativeToActorRotation: %s"), SpawnIsRelativeToActorRotation ? TEXT("TRUE") : TEXT("FALSE"));
}

/*

	NEXT SPAWN

*/

void UProjectileSpawnComponent::nextSpawn()
{
	//Order Matters
	nextSpawnActor();
	nextSpawnInfoIndexes();
	nextSpawnLocation();
	nextSpawnTime();
}

void UProjectileSpawnComponent::nextSpawnActor()
{
	m_currentSpawnActorIndex++;

	if (m_currentSpawnActorIndex > m_maxSpawnActorIndex)
	{
		m_currentSpawnActorIndex = 0;
	}


}

void UProjectileSpawnComponent::nextSpawnLocation()
{

	FVector spawnSpotCenter;
	FRotator spawnRotationCenter;
	if (GetOwner() != nullptr)
	{
		spawnSpotCenter = GetOwner()->GetActorLocation();
		spawnRotationCenter = GetOwner()->GetActorRotation();
	}

	FVector distanceToAdd = FVector(0, 0, 0);
	//y (right)  = pitch because x is forward
	//z (up) = yaw
	//x (forward) = roll



	for (size_t i = 0; i < SpawnSpots.Num(); i++)
	{

		spawnRotationCenter.Pitch = SpawnSpots[i].SpawnDegreesFromCenterOnY[m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesYIndex];
		spawnRotationCenter.Yaw = SpawnSpots[i].SpawnDegreesFromCenterOnZ[m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesZIndex];
		spawnRotationCenter.Roll = SpawnSpots[i].SpawnDegreesFromCenterOnX[m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesXIndex];

		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnLocation() - SPAWN ROTATIONS"));
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnLocation() - CURRENT SPAWN ACTOR INDEX: %d"), m_currentSpawnActorIndex);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnLocation() - SpawnDegrees X: %f"), spawnRotationCenter.Roll);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnLocation() - SpawnDegrees Y: %f"), spawnRotationCenter.Pitch);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnLocation() - SpawnDegrees Z: %f"), spawnRotationCenter.Yaw);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnLocation() - SpawnDegrees X Current Index: %d"), m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesXIndex);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnLocation() - SpawnDegrees Y Current Index: %d"), m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesYIndex);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnLocation() - SpawnDegrees Z Current Index: %d"), m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesZIndex);

		if (SpawnIsRelativeToActorRotation)
		{
			spawnRotationCenter += GetOwner()->GetActorRotation();
		}

		m_spawnSpotsIndexInfo[i].CurrentSpawnSpotRotation = spawnRotationCenter;

		distanceToAdd = m_spawnSpotsIndexInfo[i].CurrentSpawnSpotRotation.Vector().GetSafeNormal(0);

		distanceToAdd *= SpawnSpots[i].SpawnRadiuses[m_spawnSpotsIndexInfo[i].CurrentSpawnRadiusIndex];

		spawnSpotCenter += distanceToAdd;
	}


	m_spawnLocation = spawnSpotCenter;

}

void UProjectileSpawnComponent::nextSpawnInfoIndexes()
{
	nextSpawnInfoIndexesIncrease();
	nextSpawnInfoIndexesCheck();
}

void UProjectileSpawnComponent::nextSpawnInfoIndexesIncrease()
{

	size_t spawnSpotQuantity = m_spawnSpotsIndexInfo.Num() - 1 > 0 ? m_spawnSpotsIndexInfo.Num() - 1 : 0;
	size_t biggestMaxIndex = 0;
	size_t currentIndex = 0;

	//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesIncrease() - INDEX INCREASE"));


	for (size_t i = spawnSpotQuantity; i > 0; i--)
	{
		if (i > 0)
		{
			//Check biggest Index
			biggestMaxIndex = m_spawnSpotsIndexInfo[i].MaxSpawnRadiusIndex;
			biggestMaxIndex =
				biggestMaxIndex < m_spawnSpotsIndexInfo[i].MaxSpawnDegreesXIndex ?
				m_spawnSpotsIndexInfo[i].MaxSpawnDegreesXIndex :
				biggestMaxIndex < m_spawnSpotsIndexInfo[i].MaxSpawnDegreesYIndex ?
				m_spawnSpotsIndexInfo[i].MaxSpawnDegreesYIndex :
				biggestMaxIndex < m_spawnSpotsIndexInfo[i].MaxSpawnDegreesZIndex ?
				m_spawnSpotsIndexInfo[i].MaxSpawnDegreesZIndex : biggestMaxIndex;

			//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesIncrease() - Biggest Max INDEX: %d"), biggestMaxIndex);

			//Assign index based on biggest index
			currentIndex =
				biggestMaxIndex == m_spawnSpotsIndexInfo[i].MaxSpawnRadiusIndex ?
				m_spawnSpotsIndexInfo[i].CurrentSpawnRadiusIndex :
				biggestMaxIndex == m_spawnSpotsIndexInfo[i].MaxSpawnDegreesXIndex ?
				m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesXIndex :
				biggestMaxIndex == m_spawnSpotsIndexInfo[i].MaxSpawnDegreesYIndex ?
				m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesYIndex :
				biggestMaxIndex == m_spawnSpotsIndexInfo[i].MaxSpawnDegreesZIndex ?
				m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesZIndex : 0;

			//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesIncrease() - Current INDEX: %d"), currentIndex);


			if (currentIndex == biggestMaxIndex)
			{
				m_spawnSpotsIndexInfo[i - 1].CurrentSpawnRadiusIndex++;
				m_spawnSpotsIndexInfo[i - 1].CurrentSpawnDegreesXIndex++;
				m_spawnSpotsIndexInfo[i - 1].CurrentSpawnDegreesYIndex++;
				m_spawnSpotsIndexInfo[i - 1].CurrentSpawnDegreesZIndex++;

				//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesIncrease() - SpawnDegrees X PAST Index: %d"), m_spawnSpotsIndexInfo[i - 1].CurrentSpawnDegreesXIndex);
				//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesIncrease() - SpawnDegrees Y PAST Index: %d"), m_spawnSpotsIndexInfo[i - 1].CurrentSpawnDegreesYIndex);
				//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesIncrease() - SpawnDegrees Z PAST Index: %d"), m_spawnSpotsIndexInfo[i - 1].CurrentSpawnDegreesZIndex);

			}
		}
	}
}

void UProjectileSpawnComponent::nextSpawnInfoIndexesCheck()
{
	UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesIncrease() - INDEX CHECK"));

	//Increase index of last spawn spot
	if (m_spawnSpotsIndexInfo.Num() > 0)
	{
		m_spawnSpotsIndexInfo[m_spawnSpotsIndexInfo.Num() - 1].CurrentSpawnRadiusIndex++;
		m_spawnSpotsIndexInfo[m_spawnSpotsIndexInfo.Num() - 1].CurrentSpawnDegreesXIndex++;
		m_spawnSpotsIndexInfo[m_spawnSpotsIndexInfo.Num() - 1].CurrentSpawnDegreesYIndex++;
		m_spawnSpotsIndexInfo[m_spawnSpotsIndexInfo.Num() - 1].CurrentSpawnDegreesZIndex++;

		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesCheck() - SpawnDegrees X LAST Index: %d"), m_spawnSpotsIndexInfo[m_spawnSpotsIndexInfo.Num() - 1].CurrentSpawnDegreesXIndex);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesCheck() - SpawnDegrees Y LAST Index: %d"), m_spawnSpotsIndexInfo[m_spawnSpotsIndexInfo.Num() - 1].CurrentSpawnDegreesYIndex);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesCheck() - SpawnDegrees Z LAST Index: %d"), m_spawnSpotsIndexInfo[m_spawnSpotsIndexInfo.Num() - 1].CurrentSpawnDegreesZIndex);

	}


	for (size_t i = 0; i < m_spawnSpotsIndexInfo.Num(); i++)
	{
		if (m_spawnSpotsIndexInfo[i].CurrentSpawnRadiusIndex >
			m_spawnSpotsIndexInfo[i].MaxSpawnRadiusIndex)
		{
			m_spawnSpotsIndexInfo[i].CurrentSpawnRadiusIndex = 0;
		}
		if (m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesXIndex >
			m_spawnSpotsIndexInfo[i].MaxSpawnDegreesXIndex)
		{
			m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesXIndex = 0;
		}
		if (m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesYIndex >
			m_spawnSpotsIndexInfo[i].MaxSpawnDegreesYIndex)
		{
			m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesYIndex = 0;
		}
		if (m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesZIndex >
			m_spawnSpotsIndexInfo[i].MaxSpawnDegreesZIndex)
		{
			m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesZIndex = 0;
		}
	}

	//_______________________________________________

	for (size_t i = 0; i < m_spawnSpotsIndexInfo.Num(); i++)
	{
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesCheck() - CURRENT SPAWN SPOT INDEX INFO: %d"), i);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesCheck() - CURRENT SpawnRadiusIndex: %d"), m_spawnSpotsIndexInfo[i].CurrentSpawnRadiusIndex);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesCheck() - MAX	 SpawnRadiusIndex: %d"), m_spawnSpotsIndexInfo[i].MaxSpawnRadiusIndex);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesCheck() - CURRENT SpawnDegrees X Index: %d"), m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesXIndex);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesCheck() - MAX	 SpawnDegrees X Index: %d"), m_spawnSpotsIndexInfo[i].MaxSpawnDegreesXIndex);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesCheck() - CURRENT SpawnDegrees Y Index: %d"), m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesYIndex);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesCheck() - MAX	 SpawnDegrees Y Index: %d"), m_spawnSpotsIndexInfo[i].MaxSpawnDegreesYIndex);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesCheck() - CURRENT SpawnDegrees Z Index: %d"), m_spawnSpotsIndexInfo[i].CurrentSpawnDegreesZIndex);
		//UE_LOG(LogTemp, Warning, TEXT("SpawnManagerComponent - nextSpawnInfoIndexesCheck() - MAX	 SpawnDegrees Z Index: %d"), m_spawnSpotsIndexInfo[i].MaxSpawnDegreesZIndex);

	}
}

void UProjectileSpawnComponent::nextSpawnTime()
{
	m_currentTimeIndex++;

	if (m_currentTimeIndex > m_maxTimeIndex)
	{
		m_currentTimeIndex = 0;
	}

	m_currentTimeSinceSpawned = 0;
	m_maxTimeSinceSpawned = TimesForNextSpawn[m_currentTimeIndex];
}
/*

	SPAWNING

*/
void UProjectileSpawnComponent::spawnAtLocation()
{
	if (m_actorsSpawned.Num() > 0)
	{
		m_actorsSpawned[m_currentSpawnActorIndex]->SetActorLocation(m_spawnLocation);
		//m_actorsSpawned[m_currentSpawnActorIndex]->SetActorEnableCollision(true);
		//m_actorsSpawned[m_currentSpawnActorIndex]->SetActorHiddenInGame(false);
	}
}

void UProjectileSpawnComponent::spawnOnTime()
{
	m_currentTimeSinceSpawned += GetWorld()->DeltaTimeSeconds;

	if (m_currentTimeSinceSpawned >= m_maxTimeSinceSpawned)
	{
		nextSpawn();
		spawnAtLocation();
	}
}
/*

	SPAWN TYPE

*/
void UProjectileSpawnComponent::emptySpawnSpots()
{
	if (!SpawnSpots.IsEmpty())
	{
		for (size_t i = 0; i < SpawnSpots.Num(); i++)
		{
			if (SpawnSpots[i].SpawnRadiuses.Num() > 0)
			{
				SpawnSpots[i].SpawnRadiuses.Empty();
			}
			if (SpawnSpots[i].SpawnDegreesFromCenterOnX.Num() > 0)
			{
				SpawnSpots[i].SpawnDegreesFromCenterOnX.Empty();
			}
			if (SpawnSpots[i].SpawnDegreesFromCenterOnY.Num() > 0)
			{
				SpawnSpots[i].SpawnDegreesFromCenterOnY.Empty();
			}
			if (SpawnSpots[i].SpawnDegreesFromCenterOnZ.Num() > 0)
			{
				SpawnSpots[i].SpawnDegreesFromCenterOnZ.Empty();
			}
		}

		SpawnSpots.Empty();
	}

}