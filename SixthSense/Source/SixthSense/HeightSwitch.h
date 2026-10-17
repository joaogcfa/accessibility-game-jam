#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeightSwitch.generated.h"

class UStaticMeshComponent;
class USoundBase;

UCLASS()
class SIXTHSENSE_API AHeightSwitch : public AActor
{
	GENERATED_BODY()

public:
	AHeightSwitch();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Height Switch")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Height Switch")
	TObjectPtr<UStaticMeshComponent> Mesh;

	// Whose pawn changes size: 0 = sighted (keyboard), 1 = blind (DualSense)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Height Switch")
	int32 TargetPlayerIndex = 1;

	// Sizes to cycle through, in order. The first one is the starting size.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Height Switch")
	TArray<float> Scales;

	// One sound per size, same order as Scales (tells the blind player their new size)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Height Switch")
	TArray<TObjectPtr<USoundBase>> ScaleSounds;

	// How fast the size changes (scale units per second)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Height Switch")
	float ScaleSpeed = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Height Switch")
	float InteractRange = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Height Switch")
	float Cooldown = 0.5f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Height Switch")
	int32 CurrentIndex = 0;

	UFUNCTION(BlueprintCallable, Category = "Height Switch")
	void NextSize();

	UFUNCTION(BlueprintCallable, Category = "Height Switch")
	void SetSizeIndex(int32 NewIndex);

protected:
	virtual void BeginPlay() override;

private:
	void OnPressed();
	bool IsPlayerLookingAtMe() const;

	float LastPressTime = -1000.f;
	float CurrentScale = 1.f;
	float TargetScale = 1.f;
};