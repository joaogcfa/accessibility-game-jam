// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SixthSenseCharacter.h"
#include "BlindCharacter.generated.h"

class USoundBase;
/**
 * 
 */
UCLASS()
class SIXTHSENSE_API ABlindCharacter : public ASixthSenseCharacter
{
	GENERATED_BODY()
	
public:
	ABlindCharacter();

	virtual void Tick(float DeltaTime) override;

protected:
	// Sound played once per step
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footsteps")
	TObjectPtr<USoundBase> FootstepSound;

	// Distance walked between two steps, in Unreal units
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footsteps")
	float StepDistance = 180.f;

	// Below this speed the pawn counts as standing still
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footsteps")
	float MinStepSpeed = 20.f;

private:
	float DistanceSinceLastStep = 0.f;
};
