// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SixthSenseGameMode.generated.h"

/**
 *  Simple GameMode for a first person game
 */
UCLASS(abstract)
class ASixthSenseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASixthSenseGameMode();

	UPROPERTY(EditAnywhere, Category = "Pawns") TSubclassOf<APawn> SightedPawnClass;

	UPROPERTY(EditAnywhere, Category = "Pawns") TSubclassOf<APawn> BlindPawnClass;

protected:
	virtual void BeginPlay() override;

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	virtual bool ShouldSpawnAtStartSpot(AController* Player) override;

	FTimerHandle MemberTimerHandle;

	void focousAudioOnBlindPlayer();
};



