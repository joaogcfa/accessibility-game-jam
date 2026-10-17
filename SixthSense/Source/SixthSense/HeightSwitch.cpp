#include "HeightSwitch.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Engine/World.h"

AHeightSwitch::AHeightSwitch()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionProfileName(TEXT("BlockAll"));

	Scales = { 1.0f, 1.5f, 0.5f };
}

void AHeightSwitch::BeginPlay()
{
	Super::BeginPlay();

	if (Scales.Num() == 0)
	{
		Scales.Add(1.0f);
	}

	CurrentIndex = 0;
	TargetScale = Scales[0];
	CurrentScale = TargetScale;

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		EnableInput(PC);
		if (InputComponent)
		{
			InputComponent->BindKey(EKeys::E, IE_Pressed, this, &AHeightSwitch::OnPressed).bConsumeInput = false;
		}
	}
}

void AHeightSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FMath::IsNearlyEqual(CurrentScale, TargetScale, 0.001f))
	{
		return;
	}

	CurrentScale = FMath::FInterpConstantTo(CurrentScale, TargetScale, DeltaTime, ScaleSpeed);

	// Look the pawn up each time: the blind pawn may spawn after this actor starts
	if (APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, TargetPlayerIndex))
	{
		Pawn->SetActorScale3D(FVector(CurrentScale));
	}
}

void AHeightSwitch::OnPressed()
{
	if (!IsPlayerLookingAtMe())
	{
		return;
	}

	const float Now = GetWorld()->GetTimeSeconds();
	if (Now - LastPressTime < Cooldown)
	{
		return;
	}

	LastPressTime = Now;
	NextSize();
}

void AHeightSwitch::NextSize()
{
	SetSizeIndex((CurrentIndex + 1) % Scales.Num());
}

void AHeightSwitch::SetSizeIndex(int32 NewIndex)
{
	if (!Scales.IsValidIndex(NewIndex))
	{
		return;
	}

	CurrentIndex = NewIndex;
	TargetScale = FMath::Max(Scales[CurrentIndex], 0.1f);

	if (ScaleSounds.IsValidIndex(CurrentIndex) && ScaleSounds[CurrentIndex])
	{
		UGameplayStatics::PlaySound2D(this, ScaleSounds[CurrentIndex]);
	}
}

bool AHeightSwitch::IsPlayerLookingAtMe() const
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

	FCollisionQueryParams Params(SCENE_QUERY_STAT(HeightSwitchTrace), false);
	if (APawn* Pawn = PC->GetPawn())
	{
		Params.AddIgnoredActor(Pawn);
	}

	FHitResult Hit;
	const bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, ViewLoc, End, ECC_Visibility, Params);
	return bHit && Hit.GetActor() == this;
}