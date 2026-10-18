#include "Drone.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundAttenuation.h"
#include "TimerManager.h"

ADrone::ADrone()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(80.f);
	Collision->SetCollisionProfileName(TEXT("BlockAll"));
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HumAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("HumAudio"));
	HumAudio->SetupAttachment(Collision);
	HumAudio->bAutoActivate = false;

	HumAudio->bOverrideAttenuation = true;
	HumAudio->AttenuationOverrides.bAttenuate = true;
	HumAudio->AttenuationOverrides.bSpatialize = true;
	HumAudio->AttenuationOverrides.AttenuationShape = EAttenuationShape::Sphere;
	HumAudio->AttenuationOverrides.AttenuationShapeExtents = FVector(200.f, 0.f, 0.f);
	HumAudio->AttenuationOverrides.FalloffDistance = 2000.f;
}

void ADrone::BeginPlay()
{
	Super::BeginPlay();

	HitsLeft = FMath::Max(HitsToKill, 1);

	if (HumAttenuation)
	{
		HumAudio->bOverrideAttenuation = false;
		HumAudio->AttenuationSettings = HumAttenuation;
	}

	if (HumSound)
	{
		HumAudio->SetSound(HumSound);
		HumAudio->Play();
	}
}

void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCaught)
	{
		return;
	}

	if (bChasePlayer)
	{
		ChasePlayer(DeltaTime);
	}

	if (bPitchFromAim)
	{
		UpdateAimPitch();
	}
}

void ADrone::ChasePlayer(float DeltaTime)
{
	APawn* Target = UGameplayStatics::GetPlayerPawn(this, BlindPlayerIndex);
	if (!Target)
	{
		return;
	}

	const FVector ToTarget = Target->GetActorLocation() - GetActorLocation();
	const float Distance = ToTarget.Size();

	if (Distance <= KillDistance)
	{
		bCaught = true;
		HumAudio->Stop();
		if (CatchSound)
		{
			UGameplayStatics::PlaySound2D(this, CatchSound);
		}
		GetWorldTimerManager().SetTimer(RestartTimer, this, &ADrone::RestartLevel, FMath::Max(RestartDelay, 0.01f), false);
		return;
	}

	const FVector Step = ToTarget.GetSafeNormal() * MoveSpeed * DeltaTime;
	AddActorWorldOffset(Step, true);
}

void ADrone::UpdateAimPitch()
{
	if (!HumAudio->IsPlaying())
	{
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, BlindPlayerIndex);
	if (!PC)
	{
		return;
	}

	FVector ViewLoc;
	FRotator ViewRot;
	PC->GetPlayerViewPoint(ViewLoc, ViewRot);

	const FVector ToDrone = (GetActorLocation() - ViewLoc).GetSafeNormal();
	const float Dot = FVector::DotProduct(ViewRot.Vector(), ToDrone);
	const float Alpha = FMath::GetMappedRangeValueClamped(FVector2D(0.7f, 1.0f), FVector2D(0.f, 1.f), Dot);
	HumAudio->SetPitchMultiplier(FMath::Lerp(MinPitch, MaxPitch, Alpha));
}

void ADrone::RestartLevel()
{
	const FString LevelName = UGameplayStatics::GetCurrentLevelName(this, true);
	UGameplayStatics::OpenLevel(this, FName(*LevelName));
}

void ADrone::OnShot()
{
	if (HitsLeft <= 0 || bCaught)
	{
		return;
	}

	--HitsLeft;

	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}

	if (HitsLeft > 0)
	{
		return;
	}

	OnDroneDestroyed.Broadcast();
	Destroy();
}