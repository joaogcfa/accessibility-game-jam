#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScalePlate.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USoundBase;
class AToggleBlock;

UCLASS()
class SIXTHSENSE_API AScalePlate : public AActor
{
	GENERATED_BODY()

public:
	AScalePlate();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scale Plate")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scale Plate")
	TObjectPtr<UStaticMeshComponent> Mesh;

	// Detects who is standing on the plate. Resize it to sit on top of the mesh.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scale Plate")
	TObjectPtr<UBoxComponent> Trigger;

	// At or above this scale = heavy = plate sinks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale Plate")
	float HeavyScale = 1.25f;

	// At or below this scale = light = launched
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale Plate")
	float LightScale = 0.75f;

	// How far the plate sinks (cm)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale Plate")
	float SinkDepth = 30.f;

	// Sink / rise speed (cm per second)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale Plate")
	float SinkSpeed = 100.f;

	// Upward launch speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale Plate")
	float LaunchStrength = 1500.f;

	// Seconds before the same plate can launch again (only used if Launch Only Once is off)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale Plate")
	float LaunchCooldown = 1.0f;

	// Tick = the plate launches only once, ever (until ResetLaunch is called)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale Plate")
	bool bLaunchOnlyOnce = true;

	UFUNCTION(BlueprintCallable, Category = "Scale Plate")
	void ResetLaunch();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale Plate")
	TObjectPtr<AToggleBlock> TargetBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale Plate|Sound")
	TObjectPtr<USoundBase> PressSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale Plate|Sound")
	TObjectPtr<USoundBase> LaunchSound;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Scale Plate")
	bool bPressed = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Scale Plate")
	bool bHasLaunched = false;

private:
	float CurrentOffset = 0.f;
	float LastLaunchTime = -1000.f;
};