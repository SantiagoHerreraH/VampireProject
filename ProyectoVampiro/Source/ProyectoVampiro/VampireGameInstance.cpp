// Fill out your copyright notice in the Description page of Project Settings.


#include "VampireGameInstance.h"
#include "Kismet/GameplayStatics.h"


UVampireGameInstance::UVampireGameInstance() {

}

ASpawnPool* const UVampireGameInstance::GetSpawnPool()
{
	if (SpawnPool == nullptr)
	{
		SpawnPool = Cast<ASpawnPool>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnPool::StaticClass()));
	}
	if (SpawnPool != nullptr)
	{
		return SpawnPool;
	}

	UE_LOG(LogTemp, Warning, TEXT("SpawnPool is nullptr"));
	return nullptr;
}
