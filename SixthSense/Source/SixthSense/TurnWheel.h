#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurnWheel.generated.h"

class UStaticMeshComponent;
class AToggleBlock;

UCLASS()
class SIXTHSENSE_API ATurnWheel : public AActor
{
	GENERATED_BODY()

public:
	ATurnWheel();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn Wheel")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn Wheel")
	TObjectPtr<UStaticMeshComponent> WheelMesh;

	// The block this wheel moves. Pick it in the level.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn Wheel")
	TObjectPtr<AToggleBlock> TargetBlock;

	// Progress per second (0.5 = 2 seconds from bottom to top)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn Wheel")
	float TurnSpeed = 0.5f;

	// How far away the player can be (cm) while looking at it
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn Wheel")
	float InteractRange = 400.f;

	// How far the wheel spins visually from 0 to 1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn Wheel")
	float DegreesAtFull = 720.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Turn Wheel")
	float Progress = 0.f;

protected:
	virtual void BeginPlay() override;

private:
	void OnRaisePressed();
	void OnRaiseReleased();
	void OnLowerPressed();
	void OnLowerReleased();
	bool IsPlayerLookingAtMe() const;

	bool bRaiseHeld = false;
	bool bLowerHeld = false;
};