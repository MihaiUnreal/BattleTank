// Copyright ADVANCED Co.

#include "TankTurret.h"
#include "Engine/World.h"
#include <assert.h>


void UTankTurret::Rotate(float RelativeSpeed)
{
	ensure(GetWorld() != nullptr);

	// Move the barrel the right amount this frame

	// rotate all around
	float ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, +1.0f);
	float RotationChange = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.0f, NewRotation, 0.0f));
}
