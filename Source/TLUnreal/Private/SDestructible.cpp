// Fill out your copyright notice in the Description page of Project Settings.

#include "SDestructible.h"
#include "Components/BoxComponent.h"
#include "SBlackholeProjectile.h"

// Sets default values
ASDestructible::ASDestructible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	//RootComponent = BoxComp;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	//StaticMeshComp->SetupAttachment(BoxComp);
}

// Called when the game starts or when spawned
void ASDestructible::BeginPlay()
{
	Super::BeginPlay();
	//StaticMeshComp->OnComponentHit.AddDynamic(this, &ASDestructible::OnHit);

	StaticMeshComp->OnComponentBeginOverlap.AddDynamic(this, &ASDestructible::OnOverlapBegin);
}

// Called every frame
void ASDestructible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASDestructible::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASBlackholeProjectile* Projectile = Cast<ASBlackholeProjectile>(OtherActor))
	{
		Destroy(true);
	}
}

/*void ASDestructible::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ASBlackholeProjectile* Projectile = Cast<ASBlackholeProjectile>(OtherActor))
	{
		Destroy(true);
	}
}*/


