#include "ToggleBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

AToggleBlock::AToggleBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetMobility(EComponentMobility::Movable);

	CreakAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("CreakAudio"));
	CreakAudio->SetupAttachment(Mesh);
	CreakAudio->bAutoActivate = false;
}

void AToggleBlock::BeginPlay()
{
	Super::BeginPlay();

	TargetProgress = FMath::Clamp(StartProgress, 0.f, 1.f);
	CurrentHeight = FMath::Lerp(LowHeight, HighHeight, TargetProgress);
	Mesh->SetRelativeLocation(FVector(0.f, 0.f, CurrentHeight));

	if (CreakSound)
	{
		CreakAudio->SetSound(CreakSound);
	}
}

void AToggleBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TargetHeight = FMath::Lerp(LowHeight, HighHeight, TargetProgress);
	const bool bMoving = !FMath::IsNearlyEqual(CurrentHeight, TargetHeight, 0.5f);

	if (bMoving)
	{
		CurrentHeight = FMath::FInterpConstantTo(CurrentHeight, TargetHeight, DeltaTime, MoveSpeed);
		Mesh->SetRelativeLocation(FVector(0.f, 0.f, CurrentHeight));
	}

	if (CreakSound)
	{
		if (bMoving && !CreakAudio->IsPlaying())
		{
			CreakAudio->Play();
		}
		else if (!bMoving && CreakAudio->IsPlaying())
		{
			CreakAudio->Stop();
		}
	}
}

void AToggleBlock::SetProgress(float NewProgress)
{
	TargetProgress = FMath::Clamp(NewProgress, 0.f, 1.f);
}

void AToggleBlock::SetRaised(bool bRaised)
{
	SetProgress(bRaised ? 1.f : 0.f);
}