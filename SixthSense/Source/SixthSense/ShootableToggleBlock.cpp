#include "ShootableToggleBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

void AShootableToggleBlock::OnShot()
{
	if (Mesh == nullptr || LevelSounds.Num() == 0 || NumLevels < 2)
	{
		return;
	}

	// 0 = lowest position, 1 = highest, from where the mesh really is now
	const float Alpha = static_cast<float>(FMath::GetMappedRangeValueClamped(
		FVector2D(LowHeight, HighHeight), FVector2D(0.f, 1.f), Mesh->GetRelativeLocation().Z));

	const int32 Level = FMath::Clamp(FMath::RoundToInt(Alpha * (NumLevels - 1)), 0, LevelSounds.Num() - 1);

	if (LevelSounds[Level] != nullptr)
	{
		// Play at the mesh, because the mesh is what moves
		UGameplayStatics::PlaySoundAtLocation(this, LevelSounds[Level], Mesh->GetComponentLocation());
	}
}