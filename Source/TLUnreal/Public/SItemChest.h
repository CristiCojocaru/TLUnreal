// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SItemChest.generated.h"

class UMaterial;
class UParticleSystem;

UCLASS()
class TLUNREAL_API ASItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASItemChest();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation();
	void Highlight_Implementation();
	void DeHighlight_Implementation();

	UPROPERTY(EditAnywhere)
	float LidOpenPitch{ 110.0f };

	UPROPERTY(EditAnywhere)
	UMaterial* BaseMaterial;

	UPROPERTY(EditAnywhere)
	UMaterial* HighlightMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMeshComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMeshComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TreasureMeshComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* TreasureParticleSys;

	bool bChestOpen{ false };
};
