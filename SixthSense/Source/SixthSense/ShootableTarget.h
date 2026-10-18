// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shootable.h"
#include "ShootableTarget.generated.h"


class UStaticMeshComponent;
class USoundBase;

UCLASS()
class SIXTHSENSE_API AShootableTarget : public AActor, public IShootable
{
	GENERATED_BODY()
	
public:
	AShootableTarget();

	// Called by the blind player's shot trace
	virtual void OnShot() override {}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target")
	TObjectPtr<UStaticMeshComponent> Mesh;
};

// When shot, says one number
UCLASS()
class SIXTHSENSE_API AShootableDigit : public AShootableTarget
{
	GENERATED_BODY()

public:
	virtual void OnShot() override;

protected:
	// The recording of this target's number (mono WAV)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	TObjectPtr<USoundBase> DigitSound;
};