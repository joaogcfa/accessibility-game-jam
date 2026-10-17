#include "Keypad.h"
#include "ToggleBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Engine/World.h"

AKeypad::AKeypad()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionProfileName(TEXT("BlockAll"));

	DisplayText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DisplayText"));
	DisplayText->SetupAttachment(Root);
	DisplayText->SetRelativeLocation(FVector(60.f, 0.f, 80.f));
	DisplayText->SetHorizontalAlignment(EHTA_Center);
	DisplayText->SetWorldSize(40.f);
	DisplayText->SetTextRenderColor(FColor::Yellow);
}

void AKeypad::BeginPlay()
{
	Super::BeginPlay();

	UpdateDisplay();

	// Player 0 = keyboard = sighted player
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		EnableInput(PC);
		if (InputComponent)
		{
			InputComponent->BindKey(EKeys::AnyKey, IE_Pressed, this, &AKeypad::OnAnyKey).bConsumeInput = false;
		}
	}
}

void AKeypad::OnAnyKey(FKey Key)
{
	if (bSolved || !IsPlayerLookingAtMe())
	{
		return;
	}

	if (Key == EKeys::Enter)
	{
		Submit();
		return;
	}

	if (Key == EKeys::BackSpace)
	{
		Entered.Empty();
		UpdateDisplay();
		return;
	}

	const TCHAR C = KeyToChar(Key);
	if (C == 0 || Entered.Len() >= Code.Len())
	{
		return;
	}

	Entered.AppendChar(C);
	PlayFeedback(KeySound);
	UpdateDisplay();
}

TCHAR AKeypad::KeyToChar(const FKey& Key) const
{
	if (Mode == EKeypadMode::Numbers)
	{
		const FKey Digits[] = { EKeys::Zero, EKeys::One, EKeys::Two, EKeys::Three, EKeys::Four,
								EKeys::Five, EKeys::Six, EKeys::Seven, EKeys::Eight, EKeys::Nine };
		const FKey Pad[] = { EKeys::NumPadZero, EKeys::NumPadOne, EKeys::NumPadTwo, EKeys::NumPadThree, EKeys::NumPadFour,
							 EKeys::NumPadFive, EKeys::NumPadSix, EKeys::NumPadSeven, EKeys::NumPadEight, EKeys::NumPadNine };
		for (int32 i = 0; i < 10; ++i)
		{
			if (Key == Digits[i] || Key == Pad[i])
			{
				return static_cast<TCHAR>(TEXT('0') + i);
			}
		}
		return 0;
	}

	if (Key == EKeys::Up) { return TEXT('U'); }
	if (Key == EKeys::Down) { return TEXT('D'); }
	if (Key == EKeys::Left) { return TEXT('L'); }
	if (Key == EKeys::Right) { return TEXT('R'); }
	return 0;
}

void AKeypad::Submit()
{
	if (Entered.Equals(Code.TrimStartAndEnd(), ESearchCase::IgnoreCase))
	{
		bSolved = true;
		PlayFeedback(CorrectSound);
		UpdateDisplay(TEXT("OPEN"));
		if (TargetBlock)
		{
			TargetBlock->SetRaised(bRaiseTargetOnSolve);
		}
		TeleportSightedPlayer();
		OnSolved.Broadcast();
	}
	else
	{
		PlayFeedback(WrongSound);
		Entered.Empty();
		UpdateDisplay(TEXT("WRONG"));
	}
}

void AKeypad::TeleportSightedPlayer()
{
	if (!TeleportDestination)
	{
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC)
	{
		return;
	}

	APawn* Pawn = PC->GetPawn();
	if (!Pawn)
	{
		return;
	}

	const FVector Location = TeleportDestination->GetActorLocation();
	const FRotator Rotation = TeleportDestination->GetActorRotation();
	Pawn->TeleportTo(Location, Rotation);
	PC->SetControlRotation(Rotation);
}

void AKeypad::UpdateDisplay(const FString& OverrideText)
{
	FString Shown = OverrideText;
	if (Shown.IsEmpty())
	{
		Shown = Entered;
		for (int32 i = Entered.Len(); i < Code.Len(); ++i)
		{
			Shown.AppendChar(TEXT('_'));
		}
	}
	DisplayText->SetText(FText::FromString(Shown));
}

void AKeypad::ResetKeypad()
{
	bSolved = false;
	Entered.Empty();
	UpdateDisplay();
}

bool AKeypad::IsPlayerLookingAtMe() const
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

	FCollisionQueryParams Params(SCENE_QUERY_STAT(KeypadTrace), false);
	if (APawn* Pawn = PC->GetPawn())
	{
		Params.AddIgnoredActor(Pawn);
	}

	FHitResult Hit;
	const bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, ViewLoc, End, ECC_Visibility, Params);
	return bHit && Hit.GetActor() == this;
}

void AKeypad::PlayFeedback(USoundBase* Sound) const
{
	if (Sound)
	{
		UGameplayStatics::PlaySound2D(this, Sound);
	}
}