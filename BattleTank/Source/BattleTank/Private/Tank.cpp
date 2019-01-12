// Copyright ADVANCED Co.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include <assert.h>

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(const FVector& HitLocation)
{
	if (!TankAimingComponent) return;

	if (ensure(TankAimingComponent))
	{
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	}
}

// Called from Blueprint
void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (!TankAimingComponent) return;

	// Spawn a projectile at the socket location on the barrel
	if (isReloaded)
	{
		ensure(GetWorld() != nullptr);
		UTankBarrel* Barrel = TankAimingComponent->GetBarrel();

		if (ensure(Barrel))
		{
			FVector ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
			FRotator ProjectileRotation = Barrel->GetSocketRotation(FName("Projectile"));

			AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileLocation, ProjectileRotation);

			if (ensure(Projectile))
			{
				Projectile->LaunchProjectile(LaunchSpeed);
			}

			LastFireTime = FPlatformTime::Seconds();
		}
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	// get the Aiming Component instance reference (from the blueprint)
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

