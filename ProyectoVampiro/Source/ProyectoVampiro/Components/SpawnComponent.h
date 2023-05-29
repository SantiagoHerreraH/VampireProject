// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Platform.h"
#include "Containers/Array.h"

#include "Components/ActorComponent.h"
#include "SpawnComponent.generated.h"

USTRUCT(BlueprintType)
struct FSpawnInfo {

	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int NumberOfActorsToSpawn;

	FORCEINLINE FSpawnInfo& operator=(const FSpawnInfo& other) {

		ActorToSpawn = other.ActorToSpawn;
		NumberOfActorsToSpawn = NumberOfActorsToSpawn;

		return *this;
	}

};

USTRUCT(BlueprintType)
struct FSpawnedActorsGroup {

	GENERATED_BODY()

		UPROPERTY()
		TMap<AActor*, bool> ActorToSpawnStates;

	UPROPERTY()
		TArray<AActor*> ActorArray;

	FORCEINLINE FSpawnedActorsGroup& operator=(const FSpawnedActorsGroup& other) {

		ActorToSpawnStates.Empty();
		ActorToSpawnStates.Reserve(other.ActorToSpawnStates.Num());
		ActorToSpawnStates = other.ActorToSpawnStates;

		ActorArray.Empty();
		ActorArray.Reserve(other.ActorArray.Num());
		ActorArray = other.ActorArray;

		return *this;
	}
	FORCEINLINE FSpawnedActorsGroup& operator=(const FSpawnedActorsGroup* const other) {

		ActorToSpawnStates.Empty();
		ActorToSpawnStates.Reserve(other->ActorToSpawnStates.Num());
		ActorToSpawnStates = other->ActorToSpawnStates;

		ActorArray.Empty();
		ActorArray.Reserve(other->ActorArray.Num());
		ActorArray = other->ActorArray;

		return *this;
	}


};



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROYECTOVAMPIRO_API USpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USpawnComponent();
	~USpawnComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FSpawnInfo> ActorsToSpawnInfo;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		const bool DespawnActor(AActor* const actor, const TSubclassOf<AActor> classType);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		const bool SpawnActor(AActor* const actor, const TSubclassOf<AActor> classType, const FVector spawnLocation, const FRotator spawnedActorRotation, const FVector spawnedActorScale);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		const bool GetAllActorsOfClass_Map(const TSubclassOf<AActor>& actorClassType, UPARAM(ref)TMap<AActor*, bool>& mapReference);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		const bool GetActorsOfClass_Map(const TSubclassOf<AActor>& actorClassType, const int quantity_zero, UPARAM(ref)TMap < AActor*, bool>& mapReference);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		const bool GetAllActorsOfClass_Array(const TSubclassOf<AActor>& type, UPARAM(ref)TArray<AActor*>& arrayRef);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		const bool GetActorsOfClass_Array(const TSubclassOf<AActor>& type, const int quantity_one, UPARAM(ref)TArray<AActor*>& arrayRef);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		TArray<AActor*>& GetArrayOfAllActorsOfClass(const TSubclassOf<AActor>& actorTypeArray);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		TMap<AActor*, bool>& GetMapOfAllActorsOfClass(const TSubclassOf<AActor>& actorTypeMap);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		const bool CreateAllActors();


private:

	UPROPERTY()
		TMap<TSubclassOf<AActor>, FSpawnedActorsGroup> m_actorTypes;

	unsigned int m_totalNumberOfActorsToSpawn = 0;
	unsigned int m_numberOfTimesCreatedAllActors = 0;


	//Has unsafe TArray references. Used to create actors in runtime
	UPROPERTY()
		TMap<TSubclassOf<AActor>, FSpawnedActorsGroup> m_actorTypesRunTime;
	const int m_defaultMemoryReserveForTypes = 100;
	const int m_defaultMemoryReserveForActors = 10;

	const bool createAllActorsIfNotCreatedYet();
	void createAllActors();
	void reserveSpaceForRunTimeCollection();
	void createRunTimeCollection(const TSubclassOf<AActor>& actorClassType, const int numberOfActorsToCreate);
};
