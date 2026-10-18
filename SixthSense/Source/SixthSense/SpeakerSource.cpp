#include "SpeakerSource.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

ASpeakerSource::ASpeakerSource()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	Audio->SetupAttachment(Root);
	Audio->bAutoActivate = false;
}

void ASpeakerSource::PlaySpeaker()
{
	UE_LOG(LogTemp, Warning, TEXT("SpeakerSource: PlaySpeaker, sound is %s"), Sound ? TEXT("set") : TEXT("NULL"));
	if (Sound == nullptr)
	{
		return;
	}

	if (Audio->IsPlaying())
	{
		Audio->Stop();
	}

	Audio->SetSound(Sound);
	Audio->Play();
}