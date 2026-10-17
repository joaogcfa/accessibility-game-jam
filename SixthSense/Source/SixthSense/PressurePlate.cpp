// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"
#include "BlindCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
APressurePlate::APressurePlate()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	RootComponent = Trigger;
	Trigger->SetBoxExtent(FVector(100.f, 100.f, 60.f));
	Trigger->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Trigger);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnTriggerBeginOverlap);
}

void APressurePlate::SetActive(bool bNewActive)
{
	bActive = bNewActive;
}

void APressurePlate::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bActive || Cast<ABlindCharacter>(OtherActor) == nullptr)
	{
		return; // off, or not the blind player
	}

	const float Now = GetWorld()->GetTimeSeconds();
	if (Now - LastPlayTime < Cooldown)
	{
		return;
	}
	LastPlayTime = Now;

	if (DigitsSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DigitsSound, GetActorLocation());
	}
}