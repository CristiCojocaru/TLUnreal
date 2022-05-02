// Fill out your copyright notice in the Description page of Project Settings.

#include "DashProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

void ADashProjectile::ActivateInternal()
{
	ActivateTeleport();
}

void ADashProjectile::OnHitInternal()
{
	ActivateTeleport();
}

void ADashProjectile::Teleport()
{
	AActor* MyOwner = GetOwner();
	MyOwner->SetActorLocation(GetActorLocation());
	Destroy();
}

void ADashProjectile::ActivateTeleport()
{
	ParticleSystemComp->Deactivate();
	if (ExplosionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation(), GetActorRotation());
	}
	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &ADashProjectile::Teleport, TeleportDelay);
}

