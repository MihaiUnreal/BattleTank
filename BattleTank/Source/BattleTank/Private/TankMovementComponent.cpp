// Copyright ADVANCED Co.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include <assert.h>

// Called from blueprint
void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet) || !ensure(RightTrackToSet)) return;

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (ensure(LeftTrack))
	{
		LeftTrack->SetThrottle(Throw);
	}

	if (ensure(RightTrack))
	{
		RightTrack->SetThrottle(Throw);
	}
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (ensure(LeftTrack))
	{
		LeftTrack->SetThrottle(Throw);
	}

	if (ensure(RightTrack))
	{
		RightTrack->SetThrottle(- Throw);
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// NOTE! No need to call Super(), we're replacing the base implementation!

	ensure(GetOwner() != nullptr);

	// vectors in world space
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	float RequiredThrow = FVector::DotProduct(TankForward, AIForwardIntention);

	IntendMoveForward(RequiredThrow);

	FVector RotationDir = FVector::CrossProduct(AIForwardIntention, TankForward);
	//float ZSign = FMath::Abs(RotationDir.Z) / RotationDir.Z;
	//float SteeringMagnitude = RotationDir.Size();
	RequiredThrow = RotationDir.Z;// SteeringMagnitude * ZSign;

	IntendTurnRight(RequiredThrow);
}