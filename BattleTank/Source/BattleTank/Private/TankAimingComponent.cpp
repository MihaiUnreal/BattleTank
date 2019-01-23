// Copyright ADVANCED Co.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called from blueprint
void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet) || !ensure(TurretToSet)) return;

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(const FVector& HitLocation)
{
	ensure(GetWorld() != nullptr);
	ensure(GetOwner() != nullptr);
	ensure(Barrel != nullptr);

	//UE_LOG(LogTemp, Warning, TEXT("%s AimingComponent aiming at %s from %s"), *(GetOwner()->GetName()), *(HitLocation.ToString()), *(Barrel->GetComponentLocation().ToString()));

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

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
		ESuggestProjVelocityTraceOption::Type::DoNotTrace // parameter must be present to prevent bug in UnrealEngine
	);

	if (HaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();

		//UE_LOG(LogTemp, Warning, TEXT("Tank %s"), *(GetOwner()->GetName()));
		//UE_LOG(LogTemp, Warning, TEXT("Firing at %f"), LaunchSpeed);
		//UE_LOG(LogTemp, Warning, TEXT("LaunchVelocity %s"), *OutLaunchVelocity.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("AimDirection %s"), *AimDirection.ToString());

		MoveBarrelAndTurret(AimDirection);

		float Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f : TankBarrel aim solution found"), Time);
	}
	else
	{
		float Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f : TankBarrel no aim solution found"), Time);
	}
}

// Called from Blueprint
void UTankAimingComponent::Fire()
{
	// Spawn a projectile at the socket location on the barrel
	// locked fire state for AI tanks and aiming for the player tank
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		if (ensure(Barrel))
		{
			FVector ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
			FRotator ProjectileRotation = Barrel->GetSocketRotation(FName("Projectile"));

			ensure(GetWorld() != nullptr);

			AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileLocation, ProjectileRotation);

			if (ensure(Projectile))
			{
				Projectile->LaunchProjectile(LaunchSpeed);
			}

			LastFireTime = FPlatformTime::Seconds();

			// update ammo amount per fire
			if (AmmoAmount > 0)
			{
				AmmoAmount--;
			}
		}
	}
}

void UTankAimingComponent::MoveBarrelAndTurret(const FVector& AimDirection)
{
	if (ensure(Barrel))
	{
		// work-out the difference between the current barrel rotation and AimDirection (as rotation)
		FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
		FRotator AimAsRotator = AimDirection.Rotation();
		FRotator DeltaRotator = AimAsRotator - BarrelRotator;

		//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator %s"), *AimAsRotator.ToString());

		Barrel->Elevate(DeltaRotator.Pitch);

		// we must guard the turret rotation info forcing it to take the shortest route
		// meaning if the rotation delta_angle > 180 degrees, then its shorter to 
		// to rotate - delta_angle degrees
		if (FMath::Abs(DeltaRotator.Yaw) >= 180.0f)
		{
			DeltaRotator.Yaw *= -1.0f;
		}
		Turret->Rotate(DeltaRotator.Yaw);
	}
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// first time fire after a delay
	LastFireTime = FPlatformTime::Seconds();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// update firing state
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}

	// update ammo state
	if (AmmoAmount == 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (ensure(Barrel))
	{
		return AimDirection.Equals(Barrel->GetForwardVector(), 0.01f);
	}

	return false;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetAmmoAmount() const
{
	return AmmoAmount;
}