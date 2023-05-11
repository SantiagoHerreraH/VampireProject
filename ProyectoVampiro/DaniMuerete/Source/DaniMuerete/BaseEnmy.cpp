// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnmy.h"
#include "BaseEnemyController.h"


// Sets default values
ABaseEnmy::ABaseEnmy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseEnmy::BeginPlay()
{
	Super::BeginPlay();

	//ABaseEnemyController* cotr = Cast<ABaseEnemyController>( GetController());
	//cotr->SetPlayer(playerToPursuit);
	//cotr->BeginPlay();
	
}

// Called every frame
void ABaseEnmy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnmy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


