// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyController.h"
#include "GameFramework/Character.h"


void ABaseEnemyController::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<ACharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());


}
void ABaseEnemyController::Tick(float DeltaSeconds)
{
	MoveToActor(player);

}

void ABaseEnemyController::OnMoveCompleted(FAIRequestID RequestID,EPathFollowingResult::Type Result) 
{
	//AquiSequitaVidaOLoqueseea
}

