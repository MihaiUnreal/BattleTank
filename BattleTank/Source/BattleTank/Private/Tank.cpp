// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// create the TankAimingComponent (as child of Tank)
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAt(const FVector& HitLocation)
{
	if (TankAimingComponent)
	{
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	}
}

// Called from blueprint
void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (TankAimingComponent)
	{
		TankAimingComponent->SetBarrelReference(BarrelToSet);
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

