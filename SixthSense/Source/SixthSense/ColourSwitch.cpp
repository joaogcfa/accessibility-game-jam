#include "ColourSwitch.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "TimerManager.h"

AColourSwitch::AColourSwitch()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionProfileName(TEXT("BlockAll"));
}

void AColourSwitch::BeginPlay()
{
	Super::BeginPlay();

	SetActiveColour(StartColour);

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		EnableInput(PC);
		if (InputComponent)
		{
			InputComponent->BindKey(EKeys::E, IE_Pressed, this, &AColourSwitch::OnPressed).bConsumeInput = false;
		}
	}

	if (AutoSwitchSeconds > 0.f)
	{
		GetWorldTimerManager().SetTimer(AutoSwitchTimer, this, &AColourSwitch::Flip, AutoSwitchSeconds, true);
	}
}

void AColourSwitch::OnPressed()
{
	if (!IsPlayerLookingAtMe())
	{
		return;
	}

	const float Now = GetWorld()->GetTimeSeconds();
	if (Now - LastFlipTime < Cooldown)
	{
		return;
	}

	LastFlipTime = Now;
	Flip();
}

void AColourSwitch::Flip()
{
	SetActiveColour(ActiveColour == EBlockColour::Red ? EBlockColour::Blue : EBlockColour::Red);
}

void AColourSwitch::SetActiveColour(EBlockColour NewColour)
{
	ActiveColour = NewColour;

	for (TActorIterator<AColourBlock> It(GetWorld()); It; ++It)
	{
		It->SetSolid(It->Colour == ActiveColour);
	}

	USoundBase* Sound = (ActiveColour == EBlockColour::Red) ? RedSound.Get() : BlueSound.Get();
	if (Sound)
	{
		UGameplayStatics::PlaySound2D(this, Sound);
	}

	OnColourChanged.Broadcast(ActiveColour);
}

bool AColourSwitch::IsPlayerLookingAtMe() const
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC || !GetWorld())
	{
		return false;
	}

	FVector ViewLoc;
	FRotator ViewRot;
	PC->GetPlayerViewPoint(ViewLoc, ViewRot);
	const FVector End = ViewLoc + ViewRot.Vector() * InteractRange;

	FCollisionQueryParams Params(SCENE_QUERY_STAT(ColourSwitchTrace), false);
	if (APawn* Pawn = PC->GetPawn())
	{
		Params.AddIgnoredActor(Pawn);
	}

	FHitResult Hit;
	const bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, ViewLoc, End, ECC_Visibility, Params);
	return bHit && Hit.GetActor() == this;
}