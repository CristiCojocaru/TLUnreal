// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SMagicProjectile.h"
#include "DashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TLUNREAL_API ADashProjectile : public ASMagicProjectile
{
	GENERATED_BODY()
	

protected:
	void ActivateInternal() override;
	void Teleport();

	UPROPERTY(EditAnywhere)
	float TeleportDelay{ 0.2f };

	FTimerHandle TimerHandle_Teleport;

	void OnHitInternal() override;

	void ActivateTeleport();
};
