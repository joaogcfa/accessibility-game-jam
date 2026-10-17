// Copyright Epic Games, Inc. All Rights Reserved.

#include "SixthSenseGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerStart.h"

ASixthSenseGameMode::ASixthSenseGameMode()
{
	// stub
}

void ASixthSenseGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::CreatePlayer(this, 1, true);

	GetWorldTimerManager().SetTimer(
		MemberTimerHandle,               
		this,                            
		&ASixthSenseGameMode::focousAudioOnBlindPlayer,     
		0.1f,                            
		false                            
	);
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

AActor* ASixthSenseGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	APlayerController* playerController = Cast<APlayerController>(Player);
	if (playerController == nullptr) {
		return Super::ChoosePlayerStart_Implementation(Player);
	}
	else {
		ULocalPlayer* localPlayer = playerController->GetLocalPlayer();
		if (localPlayer == nullptr) return Super::ChoosePlayerStart_Implementation(Player);
		UE_LOG(LogTemp, Warning, TEXT("Start requested for local player %d"), localPlayer->GetLocalPlayerIndex());

		FName wantedTag;
		if (localPlayer->GetLocalPlayerIndex() == 1) wantedTag = FName("Blind");
		if (localPlayer->GetLocalPlayerIndex() == 0) wantedTag = FName("Sighted");

		TArray<AActor*> starts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), starts);

		for (AActor* actor : starts) {
			APlayerStart* start = Cast<APlayerStart>(actor);
			if (start != nullptr && start->PlayerStartTag == wantedTag) {
				return start;
			}
		}
		return Super::ChoosePlayerStart_Implementation(Player);
	}

}

bool ASixthSenseGameMode::ShouldSpawnAtStartSpot(AController* Player)
{
	return false;
}

void ASixthSenseGameMode::focousAudioOnBlindPlayer()
{
	APlayerController* sightedPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	APlayerController* blindPlayerController = UGameplayStatics::GetPlayerController(this, 1);

	if (sightedPlayerController == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Couldnt get sightedPlayerController after timer"));
		return ;
	}
	if (blindPlayerController == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Couldnt get blindPlayerController after timer"));
		return ;
	}
	APawn* blindPawn = blindPlayerController->GetPawn();
	if (blindPawn == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Couldnt get blindPawn"));
		return;
	}

	sightedPlayerController->SetAudioListenerOverride(blindPawn->GetRootComponent(), FVector::ZeroVector, FRotator::ZeroRotator);

	UE_LOG(LogTemp, Warning, TEXT("AUdio OVerride done!"));



}
