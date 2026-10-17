// Fill out your copyright notice in the Description page of Project Settings.


#include "BlindCharacter.h"
#include "ShootableTarget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "DrawDebugHelpers.h"
#include "Sound/SoundBase.h"


ABlindCharacter::ABlindCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABlindCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	// Add our own mapping context (the shoot button) to this player's input
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (BlindMappingContext != nullptr)
				{
					Subsystem->AddMappingContext(BlindMappingContext, 1);
				}
			}
		}
	}
}

void ABlindCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ShootAction != nullptr)
		{
			EIC->BindAction(ShootAction, ETriggerEvent::Started, this, &ABlindCharacter::Fire);
		}
	}
}

void ABlindCharacter::Fire()
{
	if (ShotSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ShotSound, GetActorLocation());
	}

	const FVector Start = GetPawnViewLocation();
	const FVector End = Start + GetControlRotation().Vector() * FireRange;

	FHitResult Hit;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(BlindFire), false, this);

	const bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

	// Debug line, visible in the editor only. Delete once it works.
	DrawDebugLine(GetWorld(), Start, bHit ? Hit.ImpactPoint : End, FColor::Red, false, 2.f);

	if (bHit)
	{
		if (AShootableTarget* Target = Cast<AShootableTarget>(Hit.GetActor()))
		{
			Target->OnShot();
		}
	}
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