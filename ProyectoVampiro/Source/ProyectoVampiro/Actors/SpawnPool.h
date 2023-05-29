// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../Components/SpawnComponent.h"

#include "SpawnPool.generated.h"

UCLASS()
class PROYECTOVAMPIRO_API ASpawnPool : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FSpawnInfo> ActorsToSpawnInfo;

	UFUNCTION(BlueprintCallable, Category = "Spawn Pool")
		const bool DespawnActor(AActor* const actor, const TSubclassOf<AActor> classType);

	UFUNCTION(BlueprintCallable, Category = "Spawn Pool")
		const bool SpawnActor(AActor* const actor, const TSubclassOf<AActor> classType, const FVector spawnLocation, const FRotator spawnedActorRotation, const FVector spawnedActorScale);

	UFUNCTION(BlueprintCallable, Category = "Spawn Pool")
		const bool GetAllActorsOfClass_Map(const TSubclassOf<AActor> actorClassType, UPARAM(ref)TMap<AActor*, bool>& mapReference);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		const bool GetActorsOfClass_Map(const TSubclassOf<AActor>& actorClassType, const int quantity_zero, UPARAM(ref)TMap < AActor*, bool>& mapReference);

	UFUNCTION(BlueprintCallable, Category = "Spawn Pool")
		const bool GetAllActorsOfClass_Array(const TSubclassOf<AActor>  type, UPARAM(ref)TArray<AActor*>& arrayRef);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		const bool GetActorsOfClass_Array(const TSubclassOf<AActor>& type, const int quantity_one, UPARAM(ref)TArray<AActor*>& arrayRef);

	UFUNCTION(BlueprintCallable, Category = "Spawn Pool")
		TArray<AActor*>& GetArrayOfAllActorsOfClass(const TSubclassOf<AActor>& actorTypeArray);

	UFUNCTION(BlueprintCallable, Category = "Spawn Pool")
		TMap<AActor*, bool>& GetMapOfAllActorsOfClass(const TSubclassOf<AActor>& actorTypeMap);



private:

	UPROPERTY()
		USpawnComponent* SpawnPoolComponent = nullptr;

	bool m_Initialized = false;
	void initializeIfNotInitializedYet();
	void initialize();

};
