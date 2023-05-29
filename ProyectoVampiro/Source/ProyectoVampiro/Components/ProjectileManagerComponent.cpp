// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileManagerComponent.h"
#include "Kismet/GameplayStatics.h"

#include "../DataAssets/ProjectileGrowthType.h"
#include "../Actors/ProjectileController.h"
#include "../VampireGameInstance.h"

// Sets default values for this component's properties
UProjectileManagerComponent::UProjectileManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProjectileManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	initialize();

}


// Called every frame
void UProjectileManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

const bool UProjectileManagerComponent::SetProjectileGrowthType(UProjectileGrowthType* const type, const int index)
{

	if (checkIndex(index))
	{
		AProjectileController* currentController = Cast<AProjectileController>(m_ProjectileControllers[index]);

		if (currentController != nullptr)
		{
			return currentController->SetProjectileGrowthType(type);
		}
	}

	return false;
}

const bool UProjectileManagerComponent::UpdateProjectileBehaviour()
{
	AProjectileController* currentController = nullptr;
	for (size_t i = 0; i < m_ProjectileControllers.Num(); i++)
	{
		currentController = Cast<AProjectileController>(m_ProjectileControllers[i]);

		if (currentController != nullptr)
		{
			currentController->SetActorLocation(GetOwner()->GetActorLocation());
			currentController->SetActorRotation(GetOwner()->GetActorRotation());
			return currentController->UpdateProjectileBehaviour();
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("ProjectileManager - UpdateProjectileBehaviour - FALSE"));
	return false;
}

const bool UProjectileManagerComponent::NextLevel(const int controllerIndex)
{
	if (checkIndex(controllerIndex))
	{
		AProjectileController* currentController = Cast<AProjectileController>(m_ProjectileControllers[controllerIndex]);

		if (currentController != nullptr)
		{
			return currentController->NextLevel();
		}
		if (currentController == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("ProjectileManager - NextLevel - currentController is nullptr"));
		}
	}

	return false;
}

const bool UProjectileManagerComponent::LastLevel(const int projectileControllerIndex)
{
	if (checkIndex(projectileControllerIndex))
	{
		AProjectileController* currentController = Cast<AProjectileController>(m_ProjectileControllers[projectileControllerIndex]);

		if (currentController != nullptr)
		{
			return currentController->LastLevel();
		}
	}

	return false;
}

const bool UProjectileManagerComponent::SetLevel(const int projectileLevel, const int controllerIndex)
{
	if (checkIndex(controllerIndex))
	{
		AProjectileController* currentController = Cast<AProjectileController>(m_ProjectileControllers[controllerIndex]);

		if (currentController != nullptr)
		{
			return currentController->SetLevel(projectileLevel);
		}
	}

	return false;
}

void UProjectileManagerComponent::initialize()
{
	UVampireGameInstance* gameInstance = Cast<UVampireGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	ASpawnPool* spawnPool = gameInstance->GetSpawnPool();
	const bool spawned = spawnPool->GetActorsOfClass_Array(ProjectileControllerClassToManage, ProjectileControllerQuantity, m_ProjectileControllers);

	UE_LOG(LogTemp, Warning, TEXT("ProjectileManager - initialize() - Did Spawn?: %s"), spawned ? TEXT("TRUE") : TEXT("FALSE"));
}

const bool UProjectileManagerComponent::checkIndex(int indexToCheck)
{
	if (!m_ProjectileControllers.IsEmpty())
	{
		if (indexToCheck < m_ProjectileControllers.Num() &&
			indexToCheck >= 0)
		{
			return true;
		}
	}

	return false;

}
