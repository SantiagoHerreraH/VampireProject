// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProyectoVampiro/Components/PlayerStats.h"

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Components/ActorComponent.h"
#include "LifeComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROYECTOVAMPIRO_API ULifeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
		DECLARE_DELEGATE(FKillEntity);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxLife{};
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float currentLife{};
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float damagePerTick{};
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float timeBetweenTicks{};
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool isDamageOverTime{};

	ULifeComponent();
	
	UFUNCTION(BlueprintCallable, Category = "Damage")
		void ReduceLife(float amount);
	UFUNCTION(BlueprintCallable, Category = "Damage")
		void RestoreLife(float amount);
	UFUNCTION(BlueprintCallable, Category = "Damage")
		void StartDamageOverTime(float damage, float time);
	UFUNCTION(BlueprintCallable, Category = "Damage")
		void StopDamageOverTime();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FKillEntity OnKillEntity;
};
