// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileManagerComponent.generated.h"


class AProjectileController;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROYECTOVAMPIRO_API UProjectileManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UProjectileManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
		TArray<AActor*> m_ProjectileControllers;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
		int ProjectileControllerQuantity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
		TSubclassOf<AProjectileController> ProjectileControllerClassToManage;

	UFUNCTION(BlueprintCallable, Category = "ProjectileBehaviour")
		const bool SetProjectileGrowthType(UProjectileGrowthType* const type, const int index);

	UFUNCTION(BlueprintCallable, Category = "ProjectileBehaviour")
		const bool UpdateProjectileBehaviour();

	UFUNCTION(BlueprintCallable, Category = "ProjectileBehaviour")
		const bool NextLevel(const int controllerIndex);

	UFUNCTION(BlueprintCallable, Category = "ProjectileBehaviour")
		const bool LastLevel(const int projectileControllerIndex);

	UFUNCTION(BlueprintCallable, Category = "ProjectileBehaviour")
		const bool SetLevel(const int projectileLevel, const int controllerIndex);

private:

	void initialize();
	const bool checkIndex(const int indexToCheck);

};
