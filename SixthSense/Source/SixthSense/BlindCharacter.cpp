// Fill out your copyright notice in the Description page of Project Settings.


#include "BlindCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Sound/SoundBase.h"


ABlindCharacter::ABlindCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABlindCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const UCharacterMovementComponent* Movement = GetCharacterMovement();
	const float Speed = GetVelocity().Size2D();

	if (Movement == nullptr || !Movement->IsMovingOnGround() || Speed < MinStepSpeed)
	{
		DistanceSinceLastStep = StepDistance;
		return;
	}

	DistanceSinceLastStep += Speed * DeltaTime;

	if (DistanceSinceLastStep >= StepDistance)
	{
		DistanceSinceLastStep -= StepDistance;

		if (FootstepSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FootstepSound, GetActorLocation());
		}
	}
}