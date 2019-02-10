// Copyright ADVANCED Co.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

int32 ATank::GetCurrentHealth()
{
	return CurrentHealth;
}

float ATank::GetHealthPercent() const
{
	float perc = static_cast<float>(CurrentHealth) / static_cast<float>(StartingHealth);

	//UE_LOG(LogTemp, Warning, TEXT("GetHealthPercent: %i %i %f "), CurrentHealth, StartingHealth, perc, *GetName());

	return perc;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = StartingHealth;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	int32 ActualDamageInt = FPlatformMath::RoundToInt(ActualDamage);
	ActualDamageInt = FMath::Clamp(ActualDamageInt, 0, CurrentHealth);

	UE_LOG(LogTemp, Warning, TEXT("TakeDamage: %f damage to %s"), ActualDamage, *GetName());

	if (ActualDamageInt > 0)
	{
		CurrentHealth -= ActualDamageInt;
	}

	if (CurrentHealth <= 0)
	{
		// broadcast the tank death event to all listeners 
		OnTankDeath.Broadcast();

		UE_LOG(LogTemp, Warning, TEXT("Tank Death Broadcast !!!"));
	}

	return ActualDamage;
}
