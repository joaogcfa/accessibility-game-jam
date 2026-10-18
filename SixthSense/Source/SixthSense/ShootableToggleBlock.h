#pragma once

#include "CoreMinimal.h"
#include "ToggleBlock.h"
#include "Shootable.h"
#include "ShootableToggleBlock.generated.h"

class USoundBase;

UCLASS()
class SIXTHSENSE_API AShootableToggleBlock : public AToggleBlock, public IShootable
{
	GENERATED_BODY()

public:
	virtual void OnShot() override;

protected:
	// Element 0 = lowest level ("one"), element 1 = "two", and so on (mono WAVs)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shot")
	TArray<TObjectPtr<USoundBase>> LevelSounds;

	// Must equal NumLevels on the StepSwitch that controls this block
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shot")
	int32 NumLevels = 4;
};