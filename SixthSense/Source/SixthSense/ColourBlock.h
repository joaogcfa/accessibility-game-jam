#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColourBlock.generated.h"

class UStaticMeshComponent;
class UAudioComponent;
class USoundBase;

UENUM(BlueprintType)
enum class EBlockColour : uint8
{
	Red,
	Blue
};

UCLASS()
class SIXTHSENSE_API AColourBlock : public AActor
{
	GENERATED_BODY()

public:
	AColourBlock();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Colour Block")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Colour Block")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Colour Block")
	TObjectPtr<UAudioComponent> HumAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour Block")
	EBlockColour Colour = EBlockColour::Red;

	// Looping sound played from this block while it is solid (helps the blind player find safe ground)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour Block")
	TObjectPtr<USoundBase> HumSound;

	UFUNCTION(BlueprintCallable, Category = "Colour Block")
	void SetSolid(bool bNewSolid);

	UFUNCTION(BlueprintPure, Category = "Colour Block")
	bool IsSolid() const { return bSolid; }

protected:
	virtual void BeginPlay() override;

private:
	bool bSolid = true;
};