#include "StepSwitch.h"
#include "ToggleBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Engine/World.h"

AStepSwitch::AStepSwitch()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionProfileName(TEXT("BlockAll"));
}

void AStepSwitch::BeginPlay()
{
	Super::BeginPlay();

	CurrentLevel = FMath::Clamp(StartLevel, 0, FMath::Max(NumLevels - 1, 1));
	ApplyLevel();

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		EnableInput(PC);
		if (InputComponent)
		{
			InputComponent->BindKey(EKeys::E, IE_Pressed, this, &AStepSwitch::OnUpPressed).bConsumeInput = false;
			InputComponent->BindKey(EKeys::Q, IE_Pressed, this, &AStepSwitch::OnDownPressed).bConsumeInput = false;
		}
	}
}

void AStepSwitch::OnUpPressed()
{
	if (IsPlayerLookingAtMe())
	{
		StepUp();
	}
}

void AStepSwitch::OnDownPressed()
{
	if (IsPlayerLookingAtMe())
	{
		StepDown();
	}
}

void AStepSwitch::StepUp()
{
	SetLevel(CurrentLevel + 1);
}

void AStepSwitch::StepDown()
{
	SetLevel(CurrentLevel - 1);
}

void AStepSwitch::SetLevel(int32 NewLevel)
{
	const int32 MaxLevel = FMath::Max(NumLevels - 1, 1);

	if (NewLevel < 0 || NewLevel > MaxLevel)
	{
		if (LimitSound)
		{
			UGameplayStatics::PlaySound2D(this, LimitSound);
		}
		return;
	}

	CurrentLevel = NewLevel;
	ApplyLevel();

	if (StepSound)
	{
		UGameplayStatics::PlaySound2D(this, StepSound);
	}
}

void AStepSwitch::ApplyLevel()
{
	if (!TargetBlock)
	{
		return;
	}

	const int32 MaxLevel = FMath::Max(NumLevels - 1, 1);
	TargetBlock->SetProgress(static_cast<float>(CurrentLevel) / static_cast<float>(MaxLevel));
}

bool AStepSwitch::IsPlayerLookingAtMe() const
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

	FCollisionQueryParams Params(SCENE_QUERY_STAT(StepSwitchTrace), false);
	if (APawn* Pawn = PC->GetPawn())
	{
		Params.AddIgnoredActor(Pawn);
	}

	FHitResult Hit;
	const bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, ViewLoc, End, ECC_Visibility, Params);
	return bHit && Hit.GetActor() == this;
}