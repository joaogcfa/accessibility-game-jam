// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USoundBase;

UCLASS()
class SIXTHSENSE_API APressurePlate : public AActor
{
	GENERATED_BODY()
	
public:
	APressurePlate();

	// Lets a wheel or block switch the plate on or off later
	UFUNCTION(BlueprintCallable, Category = "Plate")
	void SetActive(bool bNewActive);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Plate")
	TObjectPtr<UBoxComponent> Trigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Plate")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plate")
	bool bActive = true;

	// One recording with all the digits, e.g. "seven, three, one, nine" (mono WAV)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plate")
	TObjectPtr<USoundBase> DigitsSound;

	// Minimum seconds between two plays
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plate")
	float Cooldown = 3.f;

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	float LastPlayTime = -1000.f;
};
