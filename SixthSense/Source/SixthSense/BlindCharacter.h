// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SixthSenseCharacter.h"
#include "BlindCharacter.generated.h"

class USoundBase;
class UInputAction;
class UInputMappingContext;


UCLASS()
class SIXTHSENSE_API ABlindCharacter : public ASixthSenseCharacter
{
	GENERATED_BODY()

public:
	ABlindCharacter();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Fire();

	// ---- Footsteps ----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footsteps")
	TObjectPtr<USoundBase> FootstepSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footsteps")
	float StepDistance = 180.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footsteps")
	float MinStepSpeed = 20.f;

	// ---- Shooting ----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TObjectPtr<UInputAction> ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TObjectPtr<UInputMappingContext> BlindMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TObjectPtr<USoundBase> ShotSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float FireRange = 5000.f;

private:
	float DistanceSinceLastStep = 0.f;
};
