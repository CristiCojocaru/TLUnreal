// Fill out your copyright notice in the Description page of Project Settings.

#include "SItemChest.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASItemChest::ASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComponent");
	RootComponent = BaseMeshComp;

	LidMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("LidMeshComponent");
	LidMeshComp->SetupAttachment(RootComponent);

	TreasureMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("TreasureMeshComponent");
	TreasureMeshComp->SetupAttachment(RootComponent);

	TreasureParticleSys = CreateDefaultSubobject<UParticleSystemComponent>("TreasureParticleSystem");
	TreasureParticleSys->SetupAttachment(TreasureMeshComp);

	BaseMaterial = CreateDefaultSubobject<UMaterial>("BaseMaterial");
	HighlightMaterial = CreateDefaultSubobject<UMaterial>("HighlightMaterial");
}

// Called when the game starts or when spawned
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASItemChest::Interact_Implementation()
{
	if (bChestOpen)
	{
		LidMeshComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		bChestOpen = false;
	}
	else
	{
		LidMeshComp->SetRelativeRotation(FRotator(LidOpenPitch, 0.0f, 0.0f));
		TreasureParticleSys->Activate(true);
		bChestOpen = true;
	}
}

void ASItemChest::Highlight_Implementation()
{
	LidMeshComp->SetMaterial(0, HighlightMaterial);
}

void ASItemChest::DeHighlight_Implementation()
{
	LidMeshComp->SetMaterial(0, BaseMaterial);
}

