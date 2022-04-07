// Fill out your copyright notice in the Description page of Project Settings.

#include "SBarell.h"
#include "SMagicProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASBarell::ASBarell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = StaticMeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
}

// Called when the game starts or when spawned
void ASBarell::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMeshComp->OnComponentHit.AddDynamic(this, &ASBarell::OnHit);
}

// Called every frame
void ASBarell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASBarell::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ASMagicProjectile* Projectile = Cast<ASMagicProjectile>(OtherActor))
	{
		RadialForceComp->FireImpulse();
	}	
}
