#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputCoreTypes.h"
#include "Keypad.generated.h"

class UStaticMeshComponent;
class UTextRenderComponent;
class USoundBase;
class AToggleBlock;

UENUM(BlueprintType)
enum class EKeypadMode : uint8
{
	Numbers    UMETA(DisplayName = "Numbers 0-9"),
	Directions UMETA(DisplayName = "Arrow Keys")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKeypadSolved);

UCLASS()
class SIXTHSENSE_API AKeypad : public AActor
{
	GENERATED_BODY()

public:
	AKeypad();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Keypad")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Keypad")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Keypad")
	TObjectPtr<UTextRenderComponent> DisplayText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keypad")
	EKeypadMode Mode = EKeypadMode::Numbers;

	// Numbers mode: digits, e.g. 4721. Arrow mode: U D L R, e.g. UULR
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keypad")
	FString Code = TEXT("1234");

	// Block that moves when the code is correct (e.g. the exit door)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keypad")
	TObjectPtr<AToggleBlock> TargetBlock;

	// true = raise the block when solved, false = lower it
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keypad")
	bool bRaiseTargetOnSolve = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keypad")
	float InteractRange = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keypad|Sound")
	TObjectPtr<USoundBase> KeySound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keypad|Sound")
	TObjectPtr<USoundBase> CorrectSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keypad|Sound")
	TObjectPtr<USoundBase> WrongSound;

	// Designers: bind this in Blueprint (e.g. show end screen)
	UPROPERTY(BlueprintAssignable, Category = "Keypad")
	FOnKeypadSolved OnSolved;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Keypad")
	FString Entered;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Keypad")
	bool bSolved = false;

	UFUNCTION(BlueprintCallable, Category = "Keypad")
	void ResetKeypad();

protected:
	virtual void BeginPlay() override;

private:
	void OnAnyKey(FKey Key);
	void Submit();
	void UpdateDisplay(const FString& OverrideText = FString());
	bool IsPlayerLookingAtMe() const;
	TCHAR KeyToChar(const FKey& Key) const;
	void PlayFeedback(USoundBase* Sound) const;
};