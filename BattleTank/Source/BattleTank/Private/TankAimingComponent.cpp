// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "Engine/World.h"
#include <assert.h>

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(const FVector& HitLocation, float LaunchSpeed)
{
	assert(GetOwner() != nullptr);
	assert(Barrel != nullptr);

	//UE_LOG(LogTemp, Warning, TEXT("%s AimingComponent aiming at %s from %s"), *(GetOwner()->GetName()), *(HitLocation.ToString()), *(Barrel->GetComponentLocation().ToString()));

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	//FCollisionResponseParams ResponseParam;
	//TArray<AActor*> ActorsToIgnore;

	bool HaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::Type::DoNotTrace
	);

	if (HaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();

		//UE_LOG(LogTemp, Warning, TEXT("Tank %s"), *(GetOwner()->GetName()));
		//UE_LOG(LogTemp, Warning, TEXT("Firing at %f"), LaunchSpeed);
		//UE_LOG(LogTemp, Warning, TEXT("LaunchVelocity %s"), *OutLaunchVelocity.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("AimDirection %s"), *AimDirection.ToString());

		MoveBarrel(AimDirection);

		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f : TankBarrel aim solution found"), Time);
	}
	else
	{
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f : TankBarrel no aim solution found"), Time);
	}
}

void UTankAimingComponent::MoveBarrel(const FVector& AimDirection)
{
	// work-out the difference between the current barrel rotation and AimDirection (as rotation)
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator %s"), *AimAsRotator.ToString());

	Barrel->Elevate(5); // TODO remove magic number
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

