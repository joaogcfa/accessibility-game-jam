#include "SpeakerButton.h"
#include "SpeakerSource.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ASpeakerButton::ASpeakerButton()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionProfileName(TEXT("BlockAll"));
}

void ASpeakerButton::BeginPlay()
{
	Super::BeginPlay();

	// Player 0 = keyboard = sighted player
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		EnableInput(PC);
		if (InputComponent)
		{
			InputComponent->BindKey(EKeys::E, IE_Pressed, this, &ASpeakerButton::OnPressed).bConsumeInput = false;
		}
	}
}

void ASpeakerButton::OnPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("SpeakerButton: E pressed"));

	if (Speaker == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpeakerButton: no Speaker set"));
		return;
	}
	if (!IsPlayerLookingAtMe())
	{
		UE_LOG(LogTemp, Warning, TEXT("SpeakerButton: not looking at me"));
		return;
	}

	const float Now = GetWorld()->GetTimeSeconds();
	if (Now - LastPressTime < Cooldown)
	{
		return;
	}
	LastPressTime = Now;

	UE_LOG(LogTemp, Warning, TEXT("SpeakerButton: playing speaker"));
	Speaker->PlaySpeaker();
}

bool ASpeakerButton::IsPlayerLookingAtMe() const
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	APawn* Pawn = PC ? PC->GetPawn() : nullptr;
	if (Pawn == nullptr)
	{
		return false;
	}

	const float Dist = FVector::Dist(Pawn->GetActorLocation(), GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("SpeakerButton: distance %.0f (range %.0f)"), Dist, InteractRange);
	return Dist <= InteractRange;
}