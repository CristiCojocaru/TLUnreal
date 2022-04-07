// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("StrafeRight", this, &ASCharacter::StrafeRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
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
	//FRotator CameraRotation = GetControlRotation();
	//CameraRotation.Pitch = 0;
	//CameraRotation.Roll = 0;
	//SetActorRotation(CameraRotation);

	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	HandLocation += GetActorForwardVector() * ProjectileXDeviation;
	FTransform SpawnTM(GetActorRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(MainAttackProjectile, SpawnTM, SpawnParams);
}