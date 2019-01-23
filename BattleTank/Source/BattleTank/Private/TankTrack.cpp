// Copyright ADVANCED Co.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	// register on hit delegate
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ApplySidewaysForce();
}

// CAlled every frame
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("TankTrack OnHit!"));

	DriveTrack();
	ApplySidewaysForce();
	//reset throttle
	CurrentThrottle = 0.0f;
}

void UTankTrack::DriveTrack()
{
	ensure(GetOwner() != nullptr);

	FVector AppliedForce = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (ensure(TankRoot))
	{
		TankRoot->AddForceAtLocation(AppliedForce, ForceLocation);
	}
}

void UTankTrack::ApplySidewaysForce()
{
	// calc the slipage speed
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// calc the acceleration for this frame = speed / time
	// do the correcton in the opposite direction
	ensure(GetWorld() != nullptr);
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector CorrectionAcceleration = - SlippageSpeed / DeltaTime * GetRightVector();
	// calc and apply sideways force, F = m * a
	ensure(GetOwner() != nullptr);
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	
	if (ensure(TankRoot))
	{
		FVector CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2; // devide by 2, because e have 2 tracks
		TankRoot->AddForce(CorrectionForce);
	}
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0f, +1.0f);
}
