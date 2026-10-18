#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeakerButton.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class ASpeakerSource;

UCLASS()
class SIXTHSENSE_API ASpeakerButton : public AActor
{
	GENERATED_BODY()

public:
	ASpeakerButton();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Speaker")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Speaker")
	TObjectPtr<UStaticMeshComponent> Mesh;

	// The speaker this button switches on. Set it on the placed button in the level.
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Speaker")
	TObjectPtr<ASpeakerSource> Speaker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speaker")
	float InteractRange = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speaker")
	float Cooldown = 1.f;

	void OnPressed();
	bool IsPlayerLookingAtMe() const;

private:
	float LastPressTime = -1000.f;
};