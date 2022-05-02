// Fill out your copyright notice in the Description page of Project Settings.

#include "SBlackholeProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/SphereComponent.h"

ASBlackholeProjectile::ASBlackholeProjectile() : ASMagicProjectile()
{
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComp->SetupAttachment(RootComponent);
}

void ASBlackholeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bPowerActive)
	{
		RadialForceComp->FireImpulse();
	}
}

void ASBlackholeProjectile::ActivateInternal()
{
	bPowerActive = true;
}