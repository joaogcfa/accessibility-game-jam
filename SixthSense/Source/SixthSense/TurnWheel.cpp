#include "TurnWheel.h"
#include "ToggleBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ATurnWheel::ATurnWheel()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	WheelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelMesh"));
	WheelMesh->SetupAttachment(Root);
	WheelMesh->SetMobility(EComponentMobility::Movable);
	WheelMesh->SetCollisionProfileName(TEXT("BlockAll"));
}

void ATurnWheel::BeginPlay()
{
	Super::BeginPlay();

	if (TargetBlock)
	{
		Progress = TargetBlock->StartProgress;
	}

	// Player 0 = keyboard = sighted player
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		EnableInput(PC);
		if (InputComponent)
		{
			// bConsumeInput = false so every wheel in the level hears E/Q
			InputComponent->BindKey(EKeys::E, IE_Pressed, this, &ATurnWheel::OnRaisePressed).bConsumeInput = false;
			InputComponent->BindKey(EKeys::E, IE_Released, this, &ATurnWheel::OnRaiseReleased).bConsumeInput = false;
			InputComponent->BindKey(EKeys::Q, IE_Pressed, this, &ATurnWheel::OnLowerPressed).bConsumeInput = false;
			InputComponent->BindKey(EKeys::Q, IE_Released, this, &ATurnWheel::OnLowerReleased).bConsumeInput = false;
		}
	}
}

void ATurnWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float Dir = (bRaiseHeld ? 1.f : 0.f) - (bLowerHeld ? 1.f : 0.f);
	if (Dir != 0.f && IsPlayerLookingAtMe())
	{
		Progress = FMath::Clamp(Progress + Dir * TurnSpeed * DeltaTime, 0.f, 1.f);
		WheelMesh->SetRelativeRotation(FRotator(0.f, Progress * DegreesAtFull, 0.f));

		if (TargetBlock)
		{
			TargetBlock->SetProgress(Progress);
		}
	}
}

bool ATurnWheel::IsPlayerLookingAtMe() const
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

	FCollisionQueryParams Params(SCENE_QUERY_STAT(TurnWheelTrace), false);
	if (APawn* Pawn = PC->GetPawn())
	{
		Params.AddIgnoredActor(Pawn);
	}

	FHitResult Hit;
	const bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, ViewLoc, End, ECC_Visibility, Params);
	return bHit && Hit.GetActor() == this;
}

void ATurnWheel::OnRaisePressed() { bRaiseHeld = true; }
void ATurnWheel::OnRaiseReleased() { bRaiseHeld = false; }
void ATurnWheel::OnLowerPressed() { bLowerHeld = true; }
void ATurnWheel::OnLowerReleased() { bLowerHeld = false; }