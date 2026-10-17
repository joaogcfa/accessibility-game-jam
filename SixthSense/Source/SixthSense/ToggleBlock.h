#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToggleBlock.generated.h"

class UStaticMeshComponent;
class UAudioComponent;
class USoundBase;

UCLASS()
class SIXTHSENSE_API AToggleBlock : public AActor
{
	GENERATED_BODY()

public:
	AToggleBlock();

	virtual void Tick(float DeltaTime) override;

	// 0 = LowHeight, 1 = HighHeight
	UFUNCTION(BlueprintCallable, Category = "Toggle Block")
	void SetProgress(float NewProgress);

	UFUNCTION(BlueprintCallable, Category = "Toggle Block")
	void SetRaised(bool bRaised);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Toggle Block")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Toggle Block")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Toggle Block")
	TObjectPtr<UAudioComponent> CreakAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toggle Block")
	float LowHeight = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toggle Block")
	float HighHeight = 300.f;

	// Centimetres per second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toggle Block")
	float MoveSpeed = 200.f;

	// 0 = starts low, 1 = starts high
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toggle Block", meta = (ClampMin = "0", ClampMax = "1"))
	float StartProgress = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toggle Block")
	TObjectPtr<USoundBase> CreakSound;

protected:
	virtual void BeginPlay() override;

private:
	float TargetProgress = 0.f;
	float CurrentHeight = 0.f;
};