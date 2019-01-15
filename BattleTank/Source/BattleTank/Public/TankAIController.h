// Copyright ADVANCED Co.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	// the distance the AI tank is allowed to move towards the player tank
	UPROPERTY(EditAnywhere, Category = Setup)
	float AcceptanceRadius = 3000.0f; // in cm

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	APawn* GetControlledTank() const;
	APawn* GetPlayerTank() const;
};
