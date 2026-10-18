#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeakerTrigger.generated.h"

class UBoxComponent;
class ASpeakerSource;

UCLASS()
class SIXTHSENSE_API ASpeakerTrigger : public AActor
{
	GENERATED_BODY()

public:
	ASpeakerTrigger();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Speaker")
	TObjectPtr<UBoxComponent> Trigger;

	UPROPERTY(EditInstanceOnly, Category = "Speaker")
	TObjectPtr<ASpeakerSource> Speaker;

	// Seconds before it can trigger again
	UPROPERTY(EditAnywhere, Category = "Speaker")
	float Cooldown = 3.f;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	float LastTriggerTime = -1000.f;
};