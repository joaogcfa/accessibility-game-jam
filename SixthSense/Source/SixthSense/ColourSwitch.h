#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColourBlock.h"
#include "ColourSwitch.generated.h"

class UStaticMeshComponent;
class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnColourChanged, EBlockColour, NewColour);

UCLASS()
class SIXTHSENSE_API AColourSwitch : public AActor
{
	GENERATED_BODY()

public:
	AColourSwitch();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Colour Switch")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Colour Switch")
	TObjectPtr<UStaticMeshComponent> Mesh;

	// Which colour is solid when the level starts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour Switch")
	EBlockColour StartColour = EBlockColour::Red;

	// 0 = only the button flips it. Above 0 = also flips by itself every N seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour Switch")
	float AutoSwitchSeconds = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour Switch")
	float InteractRange = 400.f;

	// Stops double presses
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour Switch")
	float Cooldown = 0.5f;

	// Played when Red becomes solid / Blue becomes solid. Make them clearly different!
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour Switch|Sound")
	TObjectPtr<USoundBase> RedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour Switch|Sound")
	TObjectPtr<USoundBase> BlueSound;

	UPROPERTY(BlueprintAssignable, Category = "Colour Switch")
	FOnColourChanged OnColourChanged;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Colour Switch")
	EBlockColour ActiveColour = EBlockColour::Red;

	UFUNCTION(BlueprintCallable, Category = "Colour Switch")
	void Flip();

	UFUNCTION(BlueprintCallable, Category = "Colour Switch")
	void SetActiveColour(EBlockColour NewColour);

protected:
	virtual void BeginPlay() override;

private:
	void OnPressed();
	bool IsPlayerLookingAtMe() const;

	float LastFlipTime = -1000.f;
	FTimerHandle AutoSwitchTimer;
};