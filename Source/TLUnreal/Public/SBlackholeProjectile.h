// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SMagicProjectile.h"
#include "SBlackholeProjectile.generated.h"

class URadialForceComponent;

UCLASS()
class TLUNREAL_API ASBlackholeProjectile : public ASMagicProjectile
{
	GENERATED_BODY()

public:
	ASBlackholeProjectile();
	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;

	bool bPowerActive{ false };

	void ActivateInternal() override;
};
