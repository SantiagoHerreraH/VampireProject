// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProyectoVampiro/Components/LifeComponent.h"
#include "ProyectoVampiro/Interface/LifeManagerInterface.h"
#include "ProyectoVampiroCharacter.generated.h"

UCLASS(config = Game)
class AProyectoVampiroCharacter : public ACharacter, public ILifeManagerInterface
{
	GENERATED_BODY()

		/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;


public:
	//Levels
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int currentLevel{};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxLevel{};
	//Experience
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float currentXP{};
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float neededXP{};

	AProyectoVampiroCharacter();
	//Life component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		ULifeComponent* m_LifeComponent = nullptr;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ReduceLife(float amount);
	virtual void ReduceLife_Implementation(float amount) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void RestoreLife(float amount);
	virtual void RestoreLife_Implementation(float amount) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void StartDamageOverTime(float damage, float time);
	virtual void StartDamageOverTime_Implementation(float damage, float time) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void StopDamageOverTime();
	virtual void StopDamageOverTime_Implementation() override;

	//Leveling up
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void AddExperience(float xp);
	virtual void AddExperience_Implementation(float xp);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void LevelUp();
	virtual void LevelUp_Implementation();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		float TurnRateGamepad;

protected:

	void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void KillPlayer();


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

