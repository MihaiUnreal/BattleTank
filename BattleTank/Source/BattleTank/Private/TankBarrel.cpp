// Copyright ADVANCED Co.

#include "TankBarrel.h"
#include "Engine/World.h"
#include <assert.h>

void UTankBarrel::Elevate(float RelativeSpeed)
{
	ensure(GetWorld() != nullptr);

	// Move the barrel the right amount this frame
	// given a max elevation speed and frame time
	float ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, +1.0f);
	float ElevateChange = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevateChange;
	float ClmapNewElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(ClmapNewElevation, 0.0f, 0.0f));
}

