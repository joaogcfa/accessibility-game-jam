#include "Drone.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
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

	DetectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectSphere"));
	DetectSphere->SetupAttachment(Collision);
	DetectSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DetectSphere->SetHiddenInGame(true);
	DetectSphere->ShapeColor = FColor::Green;
	DetectSphere->InitSphereRadius(1000.f);
}

void ADrone::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	DetectSphere->SetSphereRadius(FMath::Max(DetectRadius, 1.f));
}

void ADrone::BeginPlay()
{
	Super::BeginPlay();

	HitsLeft = FMath::Max(HitsToKill, 1);
	StartLocation = GetActorLocation();
	bAlerted = (DetectRadius <= 0.f);

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
	const bool bInRange = (DetectRadius <= 0.f) || (Distance <= DetectRadius);

	// Wait until the player enters the radius
	if (!bAlerted)
	{
		if (!bInRange)
		{
			return;
		}
		bAlerted = true;
	}
	else if (!bStayAlerted && !bInRange)
	{
		bAlerted = false;
		return;
	}

	if (Distance <= KillDistance)
	{
		bCaught = true;
		HumAudio->Stop();
		if (CatchSound)
		{
			UGameplayStatics::PlaySound2D(this, CatchSound);
		}
		GetWorldTimerManager().SetTimer(RestartTimer, this, &ADrone::HandleCatch, FMath::Max(RestartDelay, 0.01f), false);
		return;
	}

	const FVector Step = ToTarget.GetSafeNormal() * MoveSpeed * DeltaTime;

	// 1. Try to move straight at the player
	FHitResult Hit;
	AddActorWorldOffset(Step, true, &Hit);
	if (!Hit.bBlockingHit)
	{
		return;
	}

	// 2. Blocked: slide along the wall
	const FVector Slide = FVector::VectorPlaneProject(Step, Hit.Normal) * (1.f - Hit.Time);
	if (!Slide.IsNearlyZero())
	{
		FHitResult SlideHit;
		AddActorWorldOffset(Slide, true, &SlideHit);
		if (!SlideHit.bBlockingHit)
		{
			return;
		}
	}

	// 3. Still stuck (corner or head-on): climb up to get over it, up to the height limit
	const float MaxZ = StartLocation.Z + MaxClimbHeight;
	const float CurrentZ = GetActorLocation().Z;
	if (CurrentZ < MaxZ)
	{
		const float Rise = FMath::Min(ClimbSpeed * DeltaTime, MaxZ - CurrentZ);
		AddActorWorldOffset(FVector(0.f, 0.f, Rise), true);
	}
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

void ADrone::HandleCatch()
{
	if (!RespawnPoint)
	{
		const FString LevelName = UGameplayStatics::GetCurrentLevelName(this, true);
		UGameplayStatics::OpenLevel(this, FName(*LevelName));
		return;
	}

	// Send the blind player to the respawn point
	if (APawn* Target = UGameplayStatics::GetPlayerPawn(this, BlindPlayerIndex))
	{
		const FRotator Rotation = RespawnPoint->GetActorRotation();
		Target->TeleportTo(RespawnPoint->GetActorLocation(), Rotation);
		if (AController* Controller = Target->GetController())
		{
			Controller->SetControlRotation(Rotation);
		}
	}

	// Send the drone back to its start and wait again
	SetActorLocation(StartLocation);
	bAlerted = (DetectRadius <= 0.f);
	bCaught = false;
	if (HumSound)
	{
		HumAudio->Play();
	}
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