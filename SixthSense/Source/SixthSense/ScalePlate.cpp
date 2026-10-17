#include "ScalePlate.h"
#include "ToggleBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Engine/World.h"

AScalePlate::AScalePlate()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetMobility(EComponentMobility::Movable);
	Mesh->SetCollisionProfileName(TEXT("BlockAll"));

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(Root);
	Trigger->SetBoxExtent(FVector(50.f, 50.f, 40.f));
	Trigger->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	Trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Trigger->SetGenerateOverlapEvents(true);
}

void AScalePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> Overlaps;
	Trigger->GetOverlappingActors(Overlaps, APawn::StaticClass());

	bool bHeavyOnPlate = false;
	ACharacter* LightCharacter = nullptr;

	for (AActor* Actor : Overlaps)
	{
		const float Scale = Actor->GetActorScale3D().Z;
		if (Scale >= HeavyScale)
		{
			bHeavyOnPlate = true;
		}
		else if (Scale <= LightScale)
		{
			LightCharacter = Cast<ACharacter>(Actor);
		}
	}

	// Pressed / released
	if (bHeavyOnPlate != bPressed)
	{
		bPressed = bHeavyOnPlate;
		if (bPressed && PressSound)
		{
			UGameplayStatics::PlaySound2D(this, PressSound);
		}
		if (TargetBlock)
		{
			TargetBlock->SetRaised(bPressed);
		}
	}

	// Move the plate mesh
	const float TargetOffset = bPressed ? -SinkDepth : 0.f;
	if (!FMath::IsNearlyEqual(CurrentOffset, TargetOffset, 0.1f))
	{
		CurrentOffset = FMath::FInterpConstantTo(CurrentOffset, TargetOffset, DeltaTime, SinkSpeed);
		Mesh->SetRelativeLocation(FVector(0.f, 0.f, CurrentOffset));
	}

	// Launch a small player
	if (!LightCharacter)
	{
		return;
	}

	if (bLaunchOnlyOnce && bHasLaunched)
	{
		return;
	}

	const float Now = GetWorld()->GetTimeSeconds();
	if (Now - LastLaunchTime < LaunchCooldown)
	{
		return;
	}

	bHasLaunched = true;
	LastLaunchTime = Now;
	LightCharacter->LaunchCharacter(FVector(0.f, 0.f, LaunchStrength), false, true);

	if (LaunchSound)
	{
		UGameplayStatics::PlaySound2D(this, LaunchSound);
	}
}

void AScalePlate::ResetLaunch()
{
	bHasLaunched = false;
}