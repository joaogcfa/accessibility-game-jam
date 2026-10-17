#include "ColourBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

AColourBlock::AColourBlock()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionProfileName(TEXT("BlockAll"));

	HumAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("HumAudio"));
	HumAudio->SetupAttachment(Root);
	HumAudio->bAutoActivate = false;
}

void AColourBlock::BeginPlay()
{
	Super::BeginPlay();

	if (HumSound)
	{
		HumAudio->SetSound(HumSound);
	}
}

void AColourBlock::SetSolid(bool bNewSolid)
{
	bSolid = bNewSolid;
	SetActorHiddenInGame(!bSolid);
	SetActorEnableCollision(bSolid);

	if (HumSound)
	{
		if (bSolid)
		{
			HumAudio->Play();
		}
		else
		{
			HumAudio->Stop();
		}
	}
}