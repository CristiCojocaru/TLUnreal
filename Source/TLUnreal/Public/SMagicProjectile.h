// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class TLUNREAL_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleSystemComp;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* ExplosionEffect;

	UPROPERTY(EditAnywhere)
	bool bDestroyOnHit{true};

	UPROPERTY(EditAnywhere)
	float LifeDuration{ 0.0f };

	FTimerHandle TimerHandle_Destroy;

	UPROPERTY(EditAnywhere)
	float ActivationDuration{ 0.0f };

	FTimerHandle TimerHandle_Activate;

	virtual void ActivateInternal() {};
	inline void Activate() { ActivateInternal(); };

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	virtual void OnHitInternal();

	void EndLifetime();
};
