// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"
#include <assert.h>


void UTankTurret::Rotate(float RelativeSpeed)
{
	assert(GetWorld() != nullptr);

	// Move the barrel the right amount this frame

	// rotate all around, no clamping
	float ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, +1.0f);
	float RotationChange = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.0f, NewRotation, 0.0f));
}
