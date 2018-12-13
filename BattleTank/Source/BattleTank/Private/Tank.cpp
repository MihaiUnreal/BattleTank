// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include <assert.h>

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
	if (!BarrelToSet) return;

	if (TankAimingComponent)
	{
		TankAimingComponent->SetBarrelReference(BarrelToSet);
	}
	Barrel = BarrelToSet;
}

// Called from Blueprint
void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet) return;

	if (TankAimingComponent)
	{
		TankAimingComponent->SetTurretReference(TurretToSet);
	}
}

// Called from Blueprint
void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	// Spawn a projectile at the socket location on the barrel
	if (Barrel && isReloaded)
	{
		assert(GetWorld() != nullptr);

		FVector ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator ProjectileRotation = Barrel->GetSocketRotation(FName("Projectile"));

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileLocation, ProjectileRotation);

		if (Projectile)
		{
			Projectile->LaunchProjectile(LaunchSpeed);
		}

		LastFireTime = FPlatformTime::Seconds();
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

