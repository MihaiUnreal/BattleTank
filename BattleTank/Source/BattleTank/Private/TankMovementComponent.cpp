// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

// Called from blueprint
void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet) return;
	if (!RightTrackToSet) return;

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (LeftTrack)
	{
		LeftTrack->SetThrottle(Throw);
	}

	if (RightTrack)
	{
		RightTrack->SetThrottle(Throw);
	}
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (LeftTrack)
	{
		LeftTrack->SetThrottle(Throw);
	}

	if (RightTrack)
	{
		RightTrack->SetThrottle(- Throw);
	}
}