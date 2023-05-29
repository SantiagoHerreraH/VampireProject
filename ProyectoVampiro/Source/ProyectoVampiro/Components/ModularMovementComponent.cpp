// Fill out your copyright notice in the Description page of Project Settings.


#include "ModularMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Map.h"

#include "../VampireGameInstance.h"
#include "../Actors/SpawnPool.h"


// Sets default values for this component's properties
UModularMovementComponent::UModularMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	RegisterComponent();
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickEnabled(true);

	// ...


}


// Called when the game starts
void UModularMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UModularMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

const bool UModularMovementComponent::SetMovingActors(UPARAM(ref)TArray<AActor*>& actorArray) {

	deactivateActors();
	m_actorsAndState.Empty();
	m_actorsAndState.Reserve(actorArray.Num());
	m_CurrentRotationIndex = 0;

	UE_LOG(LogTemp, Warning, TEXT("MoveComponent - SetMovingActors() - ACTOR SPECS"));


	for (size_t i = 0; i < actorArray.Num(); i++)
	{
		m_actorsAndState.Emplace(FActorAndState());
		m_actorsAndState[i].ActorPtr = actorArray[i];
		m_actorsAndState[i].MovementInfo.CurrentTimeOnMotion = 0;
		m_actorsAndState[i].MovementInfo.MaxTimeOnMotion = MovementDuration;
		m_actorsAndState[i].MovementInfo.IsActive = false;

		m_actorsAndState[i].MovementInfo.CurrentRotationIndex = m_CurrentRotationIndex;


		if (!MovementDirections.IsEmpty())
		{
			m_actorsAndState[i].MovementInfo.ProjectileRotation = MovementDirections[m_CurrentRotationIndex];
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("MoveComponent - SetMovingActors() - MoveDirections was empty"));
			m_actorsAndState[i].MovementInfo.ProjectileRotation = FRotator(0,0,0);
		}

		UE_LOG(LogTemp, Warning, TEXT("MoveComponent - SetMovingActors() - ACTOR INDEX: %d"), i);
		UE_LOG(LogTemp, Warning, TEXT("MoveComponent - SetMovingActors() - ActorRotation X: %f"), m_actorsAndState[i].MovementInfo.ProjectileRotation.Roll);
		UE_LOG(LogTemp, Warning, TEXT("MoveComponent - SetMovingActors() - ActorRotation Y: %f"), m_actorsAndState[i].MovementInfo.ProjectileRotation.Pitch);
		UE_LOG(LogTemp, Warning, TEXT("MoveComponent - SetMovingActors() - ActorRotation Z: %f"), m_actorsAndState[i].MovementInfo.ProjectileRotation.Yaw);


		m_CurrentRotationIndex++;
		if (m_CurrentRotationIndex >
			m_MaxRotationIndex)
		{
			m_CurrentRotationIndex = 0;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("MoveComponent - SetMovingActors() - Number of MOVING Projectiles: %d"), actorArray.Num());

	if (actorArray.Num() == 0)
	{
		return false;
	}

	return true;
}

const bool UModularMovementComponent::Move(AActor* const actorPtr)
{
	const bool enabled = enableActorMovement(actorPtr) && didInputMovementType();

	if (didInputMovementType())
	{
		moveActorsBasedOnActivation();
	}

	if (enabled)
	{
		//UE_LOG(LogTemp, Warning, TEXT("MoveComponent - Move() - Enabled"));
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("MoveComponent - Move() - Haven't set moving actors"));
	return false;
}

const bool UModularMovementComponent::SetMovementType(const UMovementType* const movementType)
{
	if (movementType != nullptr)
	{
		if (movementType->Movement == nullptr)
		{
			return false;
		}
		MovementType = movementType;
		Movement = movementType->Movement;
		MovementDuration = movementType->MovementDuration;
		MovementMultiplier = movementType->MovementMultiplier;
		MovementDirectionFollowsOwner = movementType->MovementDirectionFollowsOwner;
		MovementDirections = movementType->MovementDirections;
		m_CurrentRotationIndex = 0;
		m_MaxRotationIndex = movementType->MovementDirections.Num() - 1;

		if (MovementDirections.IsEmpty())
		{
			MovementDirections.Emplace(FRotator(0, 0, 0));
			m_MaxRotationIndex = movementType->MovementDirections.Num() - 1;
			UE_LOG(LogTemp, Warning, TEXT("MoveComponent - SetMovementType() -  MovementDirections was empty. Now num is: &d "), MovementDirections.Num());
		}


		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("MoveComponent - SetMovementType() - SetMovementType is nullptr"));

	return false;
}

/*

	PRIVATE

*/
const bool UModularMovementComponent::enableActorMovement(AActor* const actorPtr)
{

	for (size_t i = 0; i < m_actorsAndState.Num(); i++)
	{
		if (actorPtr == m_actorsAndState[i].ActorPtr)
		{
			m_actorsAndState[i].MovementInfo.CurrentTimeOnMotion = 0;
			m_actorsAndState[i].MovementInfo.IsActive = true;
			m_actorsAndState[i].MovementInfo.MaxTimeOnMotion = MovementDuration;

			//setActorInitialPosition
			m_actorsAndState[i].MovementInfo.StartPoint = actorPtr->GetActorLocation();

			m_actorsAndState[i].ActorPtr->SetActorEnableCollision(true);
			m_actorsAndState[i].ActorPtr->SetActorHiddenInGame(false);

			// setActorInitialRotation
			//In the future, this will rely on types of movement

			m_actorsAndState[i].MovementInfo.Goal =
				((GetOwner()->GetActorRotation().Vector().GetSafeNormal(0) *
					m_actorsAndState[i].MovementInfo.MaxTimeOnMotion *
					MovementMultiplier));

			m_actorsAndState[i].MovementInfo.ActorRotation = GetOwner()->GetActorRotation();

			//Rotation
			m_actorsAndState[i].ActorPtr->SetActorRotation(actorPtr->GetActorRotation());

			//implementRotationBasedOnLastActivated(i);

			return true;
		}
	}


	return false;
}

void UModularMovementComponent::moveActorsBasedOnActivation()
{
	FVector addedPosition;
	FRotator correctedDirection;


	for (size_t i = 0; i < m_actorsAndState.Num(); i++)
	{
		if (m_actorsAndState[i].MovementInfo.IsActive)
		{

			addedPosition = Movement->GetVectorValue(m_actorsAndState[i].MovementInfo.CurrentTimeOnMotion);

			correctedDirection = m_actorsAndState[i].MovementInfo.ProjectileRotation + addedPosition.Rotation();

			if (MovementDirectionFollowsOwner)
			{
				correctedDirection += m_actorsAndState[i].MovementInfo.ActorRotation;
			}

			addedPosition =
				correctedDirection.Vector() *
				MovementMultiplier *
				m_actorsAndState[i].MovementInfo.CurrentTimeOnMotion;

			addedPosition += m_actorsAndState[i].MovementInfo.StartPoint;

			m_actorsAndState[i].ActorPtr->SetActorLocation(addedPosition);

			//Increase
			m_actorsAndState[i].MovementInfo.CurrentTimeOnMotion += GetWorld()->DeltaTimeSeconds;

			//Reset
			if (m_actorsAndState[i].MovementInfo.CurrentTimeOnMotion >= m_actorsAndState[i].MovementInfo.MaxTimeOnMotion)
			{
				m_actorsAndState[i].MovementInfo.CurrentTimeOnMotion = 0;
				m_actorsAndState[i].MovementInfo.IsActive = false;
				//Despawn equivalent
				m_actorsAndState[i].ActorPtr->SetActorEnableCollision(false);
				m_actorsAndState[i].ActorPtr->SetActorHiddenInGame(true);
				UE_LOG(LogTemp, Warning, TEXT("MoveComponent - moveActorsBasedOnActivation() - Despawned"));
			}
		}
	}
}

const bool UModularMovementComponent::stopMovement(AActor* const actorPtr)
{

	for (size_t i = 0; i < m_actorsAndState.Num(); i++)
	{
		if (actorPtr == m_actorsAndState[i].ActorPtr)
		{
			m_actorsAndState[i].MovementInfo.CurrentTimeOnMotion = 0;
			m_actorsAndState[i].MovementInfo.IsActive = false;
			m_actorsAndState[i].MovementInfo.MaxTimeOnMotion = MovementDuration;

			//setActorInitialPosition
			m_actorsAndState[i].MovementInfo.StartPoint = actorPtr->GetActorLocation();

			return true;
		}
	}

	return false;
}


const bool UModularMovementComponent::didInputMovementType()
{
	bool isnotnull = MovementType != nullptr;

	if (isnotnull)
	{
		isnotnull = MovementType->Movement != nullptr;
	}

	return isnotnull;
}

void UModularMovementComponent::deactivateActors()
{
	if (!m_actorsAndState.IsEmpty())
	{
		for (size_t i = 0; i < m_actorsAndState.Num(); i++)
		{
			m_actorsAndState[i].ActorPtr->SetActorEnableCollision(false);
			m_actorsAndState[i].ActorPtr->SetActorHiddenInGame(true);

		}
	}
}