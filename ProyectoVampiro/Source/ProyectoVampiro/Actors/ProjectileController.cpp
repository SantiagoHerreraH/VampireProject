// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileController.h"
#include "../Components/ProjectileSpawnComponent.h"
#include "../Components/ModularMovementComponent.h"
#include "../DataAssets/ProjectileGrowthType.h"

// Sets default values
AProjectileController::AProjectileController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpawnController = CreateDefaultSubobject<UProjectileSpawnComponent>(TEXT("ProjectileSpawnController"));
	ProjectileSpawnController->RegisterComponent();
	//ProjectileSpawnController->AddToRoot();
	//AddInstanceComponent(ProjectileSpawn);

	ProjectileMovementController = CreateDefaultSubobject<UModularMovementComponent>(TEXT("ProjectileMovementController"));
	ProjectileMovementController->RegisterComponent();
	//ProjectileMovementController->AddToRoot();
	//AddInstanceComponent(ProjectileMovement);
}


// Called when the game starts or when spawned
void AProjectileController::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProjectileController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

const bool AProjectileController::SetProjectileGrowthType(const UProjectileGrowthType* const type)
{
	if (type != nullptr)
	{
		m_Initialized = true;
		ProjectileGrowthType = type;
		setSpawnLevel(m_CurrentProjectileIndex);
		setMovementLevel(m_CurrentProjectileIndex);

		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("ProjectileController - SetProjectileGrowthType() - projectile type was null"));

	return false;
}

const bool AProjectileController::UpdateProjectileBehaviour()
{
	initializeIfNotInitializedYet();

	AActor* currentActor = ProjectileSpawnController->Spawn();
	//UE_LOG(LogTemp, Warning, TEXT("ProjectileController - UpdateProjectileBehaviour() - Current Actor Location: %s"), *currentActor->GetActorLocation().ToString());

	return ProjectileMovementController->Move(currentActor);
}

const bool AProjectileController::NextLevel()
{
	initializeIfNotInitializedYet();

	if (m_CurrentProjectileIndex < ProjectileGrowthType->ProjectileGrowthType.Num() - 1)
	{
		m_CurrentProjectileIndex++;

		setSpawnLevel(m_CurrentProjectileIndex);
		setMovementLevel(m_CurrentProjectileIndex);

		return true;
	}

	return false;
}

const bool AProjectileController::LastLevel()
{
	initializeIfNotInitializedYet();

	if (m_CurrentProjectileIndex > 0)
	{
		m_CurrentProjectileIndex--;

		setSpawnLevel(m_CurrentProjectileIndex);
		setMovementLevel(m_CurrentProjectileIndex);

		return true;
	}

	return false;
}

const bool AProjectileController::SetLevel(const int projectileLevel)
{
	initializeIfNotInitializedYet();

	setSpawnLevel(projectileLevel);
	setMovementLevel(projectileLevel);

	const bool isWithinBounds =
		projectileLevel < 0 ? false :
		projectileLevel >= ProjectileGrowthType->ProjectileGrowthType.Num() ?
		false :
		true;

	return isWithinBounds;
}

/*

	PRIVATE

*/

void AProjectileController::initializeIfNotInitializedYet()
{
	if (!m_Initialized)
	{
		initialize();
	}
}

void AProjectileController::initialize()
{
	//Order matters
	m_Initialized = true;
	m_CurrentProjectileIndex = 0;
	setSpawnLevel(m_CurrentProjectileIndex);
	setMovementLevel(m_CurrentProjectileIndex);

}

void AProjectileController::setSpawnLevel(const int spawnLevel)
{
	UE_LOG(LogTemp, Warning, TEXT("---------------------------------------------------"));

	UE_LOG(LogTemp, Warning, TEXT("ProjectileController - setSpawnLevel() - CURRENT LEVEL: %d"), m_CurrentProjectileIndex);

	const int index =
		spawnLevel < 0 ? 0 :
		spawnLevel >= ProjectileGrowthType->ProjectileGrowthType.Num() ?
		ProjectileGrowthType->ProjectileGrowthType.Num() - 1 :
		spawnLevel;

	m_CurrentProjectileIndex = index;

	ProjectileSpawnController->
		SetSpawnParameters(
			ProjectileGrowthType->ProjectileGrowthType[index]->SpawnType,
			ProjectileGrowthType->ProjectileGrowthType[index]->ProjectileToSpawn);


}

void AProjectileController::setMovementLevel(const int movementLevel)
{
	UE_LOG(LogTemp, Warning, TEXT("---------------------------------------------------"));

	UE_LOG(LogTemp, Warning, TEXT("ProjectileController - setMovementLevel() - CURRENT LEVEL: %d"), m_CurrentProjectileIndex);

	const int index =
		movementLevel < 0 ? 0 :
		movementLevel >= ProjectileGrowthType->ProjectileGrowthType.Num() ?
		ProjectileGrowthType->ProjectileGrowthType.Num() - 1 :
		movementLevel;

	m_CurrentProjectileIndex = index;

	ProjectileMovementController->SetMovementType(ProjectileGrowthType->ProjectileGrowthType[index]->MovementType);


	if (ProjectileMovementController->SetMovingActors(ProjectileSpawnController->GetSpawnedActors()))
	{
		UE_LOG(LogTemp, Warning, TEXT("ProjectileController - initializeMovementController() - Projectiles Set"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ProjectileController - initializeMovementController() - Projectiles Not Set"));
	}
}

