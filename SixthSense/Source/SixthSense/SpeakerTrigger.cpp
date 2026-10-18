#include "SpeakerTrigger.h"
#include "Components/BoxComponent.h"
#include "SpeakerSource.h"
#include "BlindCharacter.h"

ASpeakerTrigger::ASpeakerTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);
	Trigger->SetBoxExtent(FVector(150.f, 150.f, 50.f));
	Trigger->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	Trigger->SetGenerateOverlapEvents(true);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASpeakerTrigger::OnOverlap);
}

void ASpeakerTrigger::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<ABlindCharacter>(OtherActor) || Speaker == nullptr)
	{
		return;
	}

	const float Now = GetWorld()->GetTimeSeconds();
	if (Now - LastTriggerTime < Cooldown)
	{
		return;
	}
	LastTriggerTime = Now;

	Speaker->PlaySpeaker();
}