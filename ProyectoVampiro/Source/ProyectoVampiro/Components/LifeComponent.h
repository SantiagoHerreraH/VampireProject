// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
		float m_maxLife{};
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float m_currentLife{};
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float m_dps{};
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool isDamageOverTime{};

	ULifeComponent();

	UFUNCTION(BlueprintCallable, Category = "Damage")
		void ReduceLife(float amount);
	UFUNCTION(BlueprintCallable, Category = "Damage")
		void RestoreLife(float amount);
	UFUNCTION(BlueprintCallable, Category = "Damage")
		void StartDamageOverTime(float dps);
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
