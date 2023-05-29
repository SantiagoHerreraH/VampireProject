// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileController.generated.h"

class UProjectileSpawnComponent;
class UModularMovementComponent;
class UProjectileGrowthType;

UCLASS()
class PROYECTOVAMPIRO_API AProjectileController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Component that spawns projectiles
	UPROPERTY()
		class UProjectileSpawnComponent* ProjectileSpawnController;

	UPROPERTY()
		class UModularMovementComponent* ProjectileMovementController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
		const UProjectileGrowthType* ProjectileGrowthType;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "ProjectileBehaviour")
		const bool SetProjectileGrowthType(const UProjectileGrowthType* const type);

	UFUNCTION(BlueprintCallable, Category = "ProjectileBehaviour")
		const bool UpdateProjectileBehaviour();

	UFUNCTION(BlueprintCallable, Category = "ProjectileBehaviour")
		const bool NextLevel();

	UFUNCTION(BlueprintCallable, Category = "ProjectileBehaviour")
		const bool LastLevel();

	UFUNCTION(BlueprintCallable, Category = "ProjectileBehaviour")
		const bool SetLevel(const int projectileLevel);

private:
	int m_CurrentProjectileIndex = 0;
	bool m_Initialized = false;

	void initializeIfNotInitializedYet();
	void initialize();
	void setSpawnLevel(const int spawnLevel);
	void setMovementLevel(const int movementLevel);

};
