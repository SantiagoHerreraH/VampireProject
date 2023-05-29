// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Array.h"

#include "../DataAssets/MovementType.h"

#include "ModularMovementComponent.generated.h"


USTRUCT(BlueprintType)
struct FMovementInfo {

	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentTimeOnMotion = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxTimeOnMotion = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Goal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector StartPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator ProjectileRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator ActorRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentRotationIndex;
};

USTRUCT(BlueprintType)
struct FActorAndState {

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* ActorPtr = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FMovementInfo MovementInfo;

};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROYECTOVAMPIRO_API UModularMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UModularMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Behaviour Params")
		const UMovementType* MovementType;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		const bool SetMovingActors(UPARAM(ref)TArray<AActor*>& actorArray);

	UFUNCTION(BlueprintCallable, Category = "Movement")
		const bool Move(AActor* const actorPtr);

	UFUNCTION(BlueprintCallable, Category = "Movement")
		const bool SetMovementType(const UMovementType* const inputMovementType);

private:

	UPROPERTY()
		UCurveVector* Movement;

	UPROPERTY()
		float MovementDuration = 1;

	UPROPERTY()
		float MovementMultiplier = 1000;

	UPROPERTY()
		bool MovementDirectionFollowsOwner = false;

	UPROPERTY()
		TArray<FRotator> MovementDirections;

	UPROPERTY()
		TArray<FActorAndState> m_actorsAndState;

	int m_CurrentRotationIndex;
	int m_MaxRotationIndex;

	const bool enableActorMovement(AActor* const actorPtr);
	void moveActorsBasedOnActivation();
	const bool stopMovement(AActor* const actorPtr);
	const bool didInputMovementType();
	void deactivateActors();

};
