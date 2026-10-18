#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shootable.h"
#include "Drone.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UAudioComponent;
class USoundBase;
class USoundAttenuation;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDroneDestroyed);

UCLASS()
class SIXTHSENSE_API ADrone : public AActor, public IShootable
{
	GENERATED_BODY()

public:
	ADrone();

	virtual void Tick(float DeltaTime) override;

	// From IShootable: called when the blind player's shot hits this drone
	virtual void OnShot() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone")
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone")
	TObjectPtr<UAudioComponent> HumAudio;

	// Looping MONO sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Sound")
	TObjectPtr<USoundBase> HumSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Sound")
	TObjectPtr<USoundBase> HitSound;

	// Played when the drone catches the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Sound")
	TObjectPtr<USoundBase> CatchSound;

	// Optional. If empty, built-in settings are used (inner 200, falloff 2000, spatialized)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Sound")
	TObjectPtr<USoundAttenuation> HumAttenuation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone", meta = (ClampMin = "1"))
	int32 HitsToKill = 1;

	// 1 = blind player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone")
	int32 BlindPlayerIndex = 1;

	// Fly toward the blind player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Chase")
	bool bChasePlayer = true;

	// cm per second (slow = fair for audio-only aiming)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Chase")
	float MoveSpeed = 120.f;

	// How fast it rises when blocked (to get over walls)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Chase")
	float ClimbSpeed = 200.f;

	// Max height it can climb above its start position (stops it going into a roof)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Chase")
	float MaxClimbHeight = 600.f;

	// Closer than this = caught
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Chase")
	float KillDistance = 200.f;

	// Seconds after the catch before respawn / restart
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Chase")
	float RestartDelay = 1.0f;

	// Where the blind player respawns when caught (place a Target Point). Empty = restart the level.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Chase")
	TObjectPtr<AActor> RespawnPoint;

	// Hum pitch rises as the blind player aims closer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Aim Pitch")
	bool bPitchFromAim = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Aim Pitch")
	float MinPitch = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone|Aim Pitch")
	float MaxPitch = 1.6f;

	UPROPERTY(BlueprintAssignable, Category = "Drone")
	FOnDroneDestroyed OnDroneDestroyed;

protected:
	virtual void BeginPlay() override;

private:
	void ChasePlayer(float DeltaTime);
	void UpdateAimPitch();
	void HandleCatch();

	int32 HitsLeft = 1;
	bool bCaught = false;
	FVector StartLocation = FVector::ZeroVector;
	FTimerHandle RestartTimer;
};