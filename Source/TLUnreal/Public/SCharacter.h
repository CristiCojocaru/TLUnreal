// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TLUNREAL_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> MainAttackProjectile;

	UPROPERTY(EditAnywhere)
	float ProjectileXDeviation{ 0.0f };

	UPROPERTY(EditAnywhere)
	float MaxPitchRotationLower{ 10.0f };

	UPROPERTY(EditAnywhere)
	float MaxPitchRotationUpper{ 330.0f };

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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void MoveForward(float value);
	void StrafeRight(float value);
	void LookUp(float value);
	void PrimaryAttack();
};
