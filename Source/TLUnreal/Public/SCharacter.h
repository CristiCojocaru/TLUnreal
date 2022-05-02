// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;

UCLASS()
class TLUNREAL_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TArray<TSubclassOf<AActor>> AttackList;

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float ProjectileXDeviation{ 0.0f };

	UPROPERTY(EditAnywhere, Category = "Attack")
	float ProjectileSpawnDelay{ 0.2f };

	FTimerHandle TimerHandle_PrimaryAttack;
	unsigned short AttackIndex{ 0 };


	UPROPERTY(EditAnywhere, Category = "Camera")
	float MaxPitchRotationLower{ 10.0f };

	UPROPERTY(EditAnywhere, Category = "Camera")
	float MaxPitchRotationUpper{ 330.0f };

	UPROPERTY(EditAnywhere, Category = "Camera")
	float AimRangeFactor {5000.0f};

	// Sets default values for this character's properties
	ASCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;

	void MoveForward(float value);
	void StrafeRight(float value);
	void LookUp(float value);
	void PrimaryInteract();

	void PrimaryAttack();
	void NextAttack();

	void SpawnProjectile();
	void StartAiming();
	void StopAiming();

	UPROPERTY(EditAnywhere, Category = "Aiming")
	FVector BaseOffset{ 0.0f, 0.0f, 90.0f };

	UPROPERTY(EditAnywhere, Category = "Aiming")
	FVector AimingOffset{ 100.0f, 90.0f, 90.0f };
};
