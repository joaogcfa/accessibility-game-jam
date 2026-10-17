#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StepSwitch.generated.h"

class UStaticMeshComponent;
class USoundBase;
class AToggleBlock;

UCLASS()
class SIXTHSENSE_API AStepSwitch : public AActor
{
	GENERATED_BODY()

public:
	AStepSwitch();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Step Switch")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Step Switch")
	TObjectPtr<UStaticMeshComponent> Mesh;

	// The block this switch moves. Its Low/High Height are the bottom/top levels.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Step Switch")
	TObjectPtr<AToggleBlock> TargetBlock;

	// How many heights (3 = bottom, middle, top)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Step Switch", meta = (ClampMin = "2"))
	int32 NumLevels = 3;

	// 0 = bottom
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Step Switch", meta = (ClampMin = "0"))
	int32 StartLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Step Switch")
	float InteractRange = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Step Switch|Sound")
	TObjectPtr<USoundBase> StepSound;

	// Played when already at the top or bottom
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Step Switch|Sound")
	TObjectPtr<USoundBase> LimitSound;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Step Switch")
	int32 CurrentLevel = 0;

	UFUNCTION(BlueprintCallable, Category = "Step Switch")
	void StepUp();

	UFUNCTION(BlueprintCallable, Category = "Step Switch")
	void StepDown();

	UFUNCTION(BlueprintCallable, Category = "Step Switch")
	void SetLevel(int32 NewLevel);

protected:
	virtual void BeginPlay() override;

private:
	void OnUpPressed();
	void OnDownPressed();
	void ApplyLevel();
	bool IsPlayerLookingAtMe() const;
};