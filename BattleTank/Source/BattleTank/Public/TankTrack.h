// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used for computing tank movement
   Basically the maximum drive force that is applied to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// clamp throttle value between -1 and +1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	// max force per track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = Input)
	float TrackMaxDrivingForce = 400000; // assume tank is 40 tons with 10m/s^2 acceleration


};
