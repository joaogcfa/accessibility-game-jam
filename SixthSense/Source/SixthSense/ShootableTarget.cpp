// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootableTarget.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
AShootableTarget::AShootableTarget()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh; // default collision blocks the Visibility channel, which the shot uses
}

void AShootableDigit::OnShot()
{
	if (DigitSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DigitSound, GetActorLocation());
	}
}

