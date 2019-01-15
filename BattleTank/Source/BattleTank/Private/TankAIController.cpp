// Copyright ADVANCED Co.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

//#define DEBUG_LINE
#ifdef DEBUG_LINE
#include "DrawDebugHelpers.h"
#endif

// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("TankAIController Begin Play"));

	APawn* ControlledTank = GetControlledTank();

	if (ensure(ControlledTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController possesing %s"), *(ControlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not possesing a tank!"));
	}

	APawn* PlayerTank = GetPlayerTank();

	if (ensure(PlayerTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found player tank %s"), *(PlayerTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController failed to find the player tank!"));
	}
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* ControlledTank = GetControlledTank();

	if (ensure(ControlledTank))
	{
		// aim towards the player tank
		APawn* PlayerTank = GetPlayerTank();

		// move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		if (ensure(PlayerTank))
		{
			UTankAimingComponent* TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

			if (ensure(TankAimingComponent))
			{
				TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

				TankAimingComponent->Fire();
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController failed to GET the player tank!"));
	}
}

APawn* ATankAIController::GetControlledTank() const
{
	ensure(GetPawn() != nullptr);

	return GetPawn();
}

APawn* ATankAIController::GetPlayerTank() const
{
	ensure(GetWorld() != nullptr);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	ensure(PlayerController != nullptr);

	return PlayerController->GetPawn();
}


