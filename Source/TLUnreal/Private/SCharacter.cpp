// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "SInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComponent");

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	SpringArmComp->SocketOffset = BaseOffset;

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("StrafeRight", this, &ASCharacter::StrafeRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	
	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &ASCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ASCharacter::StartAiming);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ASCharacter::StopAiming);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("NextAttack", IE_Pressed, this, &ASCharacter::NextAttack);
}

void ASCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0;
	ControlRot.Roll = 0;

	AddMovementInput(ControlRot.Vector(), value);
}

void ASCharacter::StrafeRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0;
	ControlRot.Roll = 0;

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, value);
}

void ASCharacter::LookUp(float value)
{
	float PitchRot = value;
	float ControlRotPitch = GetControlRotation().Pitch;

	if (ControlRotPitch + value < MaxPitchRotationUpper && ControlRotPitch + value > MaxPitchRotationLower)
		if(ControlRotPitch + value > 180.0f)
			PitchRot = ControlRotPitch - MaxPitchRotationUpper;
		else
			PitchRot = ControlRotPitch - MaxPitchRotationLower;

	APawn::AddControllerPitchInput(PitchRot);
}

void ASCharacter::PrimaryAttack()
{
	FRotator CameraRotation = GetControlRotation();
	CameraRotation.Pitch = 0;
	CameraRotation.Roll = 0;
	SetActorRotation(CameraRotation);

	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::SpawnProjectile, ProjectileSpawnDelay);
}

void ASCharacter::SpawnProjectile()
{
	if (AttackList.Num() > AttackIndex)
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		HandLocation += GetActorForwardVector() * ProjectileXDeviation;

		FCollisionObjectQueryParams ObjectQuery;
		ObjectQuery.AddObjectTypesToQuery(ECC_WorldStatic);

		APlayerCameraManager* PlayerCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
		FRotator CameraRotation = GetControlRotation();
		FVector MaxAimRangeLocation = PlayerCamera->GetCameraLocation() + (CameraRotation.Vector() * AimRangeFactor);

		FHitResult Hit;
		FRotator ProjectileSpawnRotation;
		if (GetWorld()->LineTraceSingleByObjectType(Hit, PlayerCamera->GetCameraLocation(), MaxAimRangeLocation, ObjectQuery))
		{
			//DrawDebugLine(GetWorld(), HandLocation, Hit.Location, FColor::Blue, false, 2.0f, 0, 2.0f);
			ProjectileSpawnRotation = UKismetMathLibrary::MakeRotFromX(Hit.Location - HandLocation);
		}
		else
		{
			//DrawDebugLine(GetWorld(), HandLocation, PlayerCamera->GetCameraLocation() + CameraRotation.Vector() * AimRangeFactor, FColor::Blue, false, 2.0f, 0, 2.0f);
			ProjectileSpawnRotation = UKismetMathLibrary::MakeRotFromX(MaxAimRangeLocation - HandLocation);
		}
		FTransform SpawnTM(ProjectileSpawnRotation, HandLocation);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		AActor* Projectile = GetWorld()->SpawnActor<AActor>(AttackList[AttackIndex], SpawnTM, SpawnParams);
		Projectile->SetOwner(this);
	}
}

void ASCharacter::NextAttack()
{
	AttackIndex++;
	if (AttackIndex >= AttackList.Num())
	{
		AttackIndex = 0;
	}
}

void ASCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void ASCharacter::StartAiming()
{
	SpringArmComp->SocketOffset = AimingOffset;
}

void ASCharacter::StopAiming()
{
	SpringArmComp->SocketOffset = BaseOffset;
}