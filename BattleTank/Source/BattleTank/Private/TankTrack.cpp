// Copyright ADVANCED Co.

#include "TankTrack.h"



void UTankTrack::SetThrottle(float Throttle)
{
	ensure(GetOwner() != nullptr);

	float ClampedThrottle = FMath::Clamp(Throttle, -1.0f, +1.0f);
	FVector AppliedForce = GetForwardVector() * ClampedThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (ensure(TankRoot))
	{
		TankRoot->AddForceAtLocation(AppliedForce, ForceLocation);
	}
}
