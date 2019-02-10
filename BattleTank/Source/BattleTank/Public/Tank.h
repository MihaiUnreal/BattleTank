// Copyright ADVANCED Co.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDeath);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	int32 GetCurrentHealth();

	// return current health as a percentage of starting health
	// between 0 and 1
	UFUNCTION(BlueprintPure, Category = Health)
	float GetHealthPercent() const;

	FTankDeath OnTankDeath; // delegate

protected:
	UPROPERTY(EditDefaultsOnly, Category = Health)
	int32 StartingHealth = 0;

	int32 CurrentHealth = 0;

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called by the engine when the actor takes damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
};
