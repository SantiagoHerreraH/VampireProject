// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"

#include "../ProyectoVampiroGameMode.h"
#include "../DataAssets/SpawnType.h"

#include "ProjectileSpawnComponent.generated.h"

/**
 *
 */

UCLASS()
class PROYECTOVAMPIRO_API UProjectileSpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UProjectileSpawnComponent();
	~UProjectileSpawnComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Behaviour Params")
		USpawnType* SpawnType = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Spawning Params")
		TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Spawning Params", meta = (ToolTip = "Only fill this in if you didn't input a SpawnType"))
		int MaxNumOfActorsToSpawn = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Behaviour Params", meta = (ToolTip = "Only fill this in if you didn't input a SpawnType"))
		TArray<FSpawnSpot> SpawnSpots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Behaviour Params", meta = (ToolTip = "Only fill this in if you didn't input a SpawnType"))
		TArray<float> TimesForNextSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Behaviour Params", meta = (ToolTip = "Only fill this in if you didn't input a SpawnType"))
		bool SpawnIsRelativeToActorRotation = false;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		AActor* const Spawn();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		TArray<AActor*>& GetSpawnedActors();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		const bool SetSpawnType(USpawnType* const spawnTypePtr);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		const bool SetSpawnParameters(USpawnType* const spawnTypeParam, const TSubclassOf<AActor> actorType);

private:

	UPROPERTY()
		TArray<AActor*> m_actorsSpawned;
	UPROPERTY()
		TArray<FSpawnSpotIndexInfo> m_spawnSpotsIndexInfo;
	UPROPERTY()
		FVector m_spawnLocation;
	UPROPERTY()
		FRotator m_spawnRotation;

	bool m_Initialized = false;

	int m_currentSpawnActorIndex = 0;
	int m_maxSpawnActorIndex = 0;

	int m_currentSpawnSpotIndex = 0;
	int m_maxSpawnSpotIndex = 0;

	int m_currentTimeIndex = 0;
	int m_maxTimeIndex = 0;

	float m_currentTimeSinceSpawned = 0;
	float m_maxTimeSinceSpawned = 0;

	//Game Mode

	void setDefaultActor();
	void getActorRefsFromSpawnPool();
	void createdefaultActorRefs();

	//Init
	void initialize();
	void setActors();

	void setSpawnSpots();
	void emptyUnnecessarySpawnSpots();
	void createSpawnSpotsOutOfSpawnType();
	void fillDefaultSpawnSpots();
	void createDefaultSpawnSpot();

	void setTimes();
	void createDefaultTimes();

	void setSpawnSpotsInfo();
	void setSpawnLocation();
	void setSpawnActorIndexes();

	void printResults();

	//Next Spawn
	void nextSpawn();
	void nextSpawnActor();
	void nextSpawnLocation();
	void nextSpawnInfoIndexes();
	void nextSpawnInfoIndexesIncrease();
	void nextSpawnInfoIndexesCheck();
	void nextSpawnTime();

	//Spawning
	void spawnAtLocation();
	void spawnOnTime();

	//Extra
	void emptySpawnSpots();

};

