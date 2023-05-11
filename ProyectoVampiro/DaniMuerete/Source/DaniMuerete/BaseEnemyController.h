// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Navigation/PathFollowingComponent.h"
//#include "Navigation/AvoidanceManager.h"
#include "BaseEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class DANIMUERETE_API ABaseEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly,Category=Pursuit)
		AActor* player {nullptr};
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


	virtual void OnMoveCompleted(FAIRequestID RequestID,EPathFollowingResult::Type Result)override;
	void SetPlayer(AActor* _actor) { player = _actor; }
};
