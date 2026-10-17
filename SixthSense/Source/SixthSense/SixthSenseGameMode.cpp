// Copyright Epic Games, Inc. All Rights Reserved.

#include "SixthSenseGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LocalPlayer.h"


ASixthSenseGameMode::ASixthSenseGameMode()
{
	// stub
}

void ASixthSenseGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::CreatePlayer(this, 1, true);
}

UClass* ASixthSenseGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{

	APlayerController* playerController = Cast<APlayerController>(InController);

	if (playerController == nullptr) {
		return Super::GetDefaultPawnClassForController_Implementation(InController);
	}
	else {
		ULocalPlayer* localPlayer = playerController->GetLocalPlayer();
		if (localPlayer == nullptr ) return Super::GetDefaultPawnClassForController_Implementation(InController);
		UE_LOG(LogTemp, Warning, TEXT("Pawn requested for local player %d"), localPlayer->GetLocalPlayerIndex());
		if (localPlayer->GetLocalPlayerIndex() == 1) return BlindPawnClass;
		if (localPlayer->GetLocalPlayerIndex() == 0) return SightedPawnClass;
		return Super::GetDefaultPawnClassForController_Implementation(InController);
	}

}
