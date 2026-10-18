#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeakerSource.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UAudioComponent;
class USoundBase;

UCLASS()
class SIXTHSENSE_API ASpeakerSource : public AActor
{
	GENERATED_BODY()

public:
	ASpeakerSource();

	// Called by the button
	UFUNCTION(BlueprintCallable, Category = "Speaker")
	void PlaySpeaker();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Speaker")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Speaker")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Speaker")
	TObjectPtr<UAudioComponent> Audio;

	// The designer picks this per speaker (mono WAV)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speaker")
	TObjectPtr<USoundBase> Sound;
};