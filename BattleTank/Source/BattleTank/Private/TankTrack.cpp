// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"



void UTankTrack::SetThrottle(float Throttle)
{
	float ClampedThrottle = FMath::Clamp(Throttle, -1.0f, +1.0f);
	FVector AppliedForce = GetForwardVector() * ClampedThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (TankRoot)
	{
		TankRoot->AddForceAtLocation(AppliedForce, ForceLocation);
	}
}
