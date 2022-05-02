// Fill out your copyright notice in the Description page of Project Settings.

#include "SInteractionComponent.h"
#include "SGameplayInterface.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckInteractibles();
}

void USInteractionComponent::CheckInteractibles()
{
	AActor* PreviouslyHighlightedActor{ HighlightedActor };
	HighlightedActor = nullptr;

	if (AActor* Owner = GetOwner())
	{
		if (ACharacter* OwnerCharacter = Cast<ACharacter>(Owner))
		{
			FCollisionObjectQueryParams ObjectQuery;
			ObjectQuery.AddObjectTypesToQuery(ECC_WorldDynamic);

			FRotator CameraRotation = OwnerCharacter->GetControlRotation();
			FVector Start = OwnerCharacter->GetActorLocation();
			FVector End = Start + (CameraRotation.Vector() * InteractionRange);

			FCollisionShape Shape;
			Shape.SetSphere(30.0f);

			TArray<FHitResult> Hits;
			GetWorld()->SweepMultiByObjectType(Hits, Start, End, FQuat::Identity, ObjectQuery, Shape);

			for (const FHitResult& Hit : Hits)
			{
				if (AActor* HitActor = Hit.GetActor())
				{
					if (HitActor->Implements<USGameplayInterface>())
					{
						if (HitActor == HighlightedActor)
						{
							PreviouslyHighlightedActor = nullptr;
						}
						else
						{
							HighlightedActor = HitActor;
						}
						break;
					}
				}
			}
		}
	}

	if (PreviouslyHighlightedActor)
	{
		ISGameplayInterface::Execute_DeHighlight(PreviouslyHighlightedActor);
		
		if (HighlightedActor)
		{
			ISGameplayInterface::Execute_Highlight(HighlightedActor);
		}
	}
}

void USInteractionComponent::PrimaryInteract()
{
	if (HighlightedActor)
	{
		ISGameplayInterface::Execute_Interact(HighlightedActor);
	}
}

