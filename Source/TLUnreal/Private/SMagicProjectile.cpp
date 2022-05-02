// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComp->InitialSpeed = 1000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = true;

	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComponent");
	ParticleSystemComp->SetupAttachment(SphereComp);
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentHit.AddDynamic(this, &ASMagicProjectile::OnHit);
	if (LifeDuration != 0)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_Destroy, this, &ASMagicProjectile::EndLifetime, LifeDuration);
	}

	if (ActivationDuration != 0)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_Activate, this, &ASMagicProjectile::Activate, ActivationDuration);
	}
}

void ASMagicProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	OnHitInternal();
}

void ASMagicProjectile::OnHitInternal()
{
	if (ExplosionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation(), GetActorRotation());
	}

	if (bDestroyOnHit)
	{
		EndLifetime();
	}
}

void ASMagicProjectile::EndLifetime()
{
	Destroy(true);
}

