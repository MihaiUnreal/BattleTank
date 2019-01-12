// Copyright ADVANCED Co.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include <assert.h>

//#define DEBUG_LINE
#ifdef DEBUG_LINE
#include "DrawDebugHelpers.h"
#endif

// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("TankAIController Begin Play"));

	ATank* ControlledTank = GetControlledTank();

	if (ensure(ControlledTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController possesing %s"), *(ControlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not possesing a tank!"));
	}

	ATank* PlayerTank = GetPlayerTank();

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

	ATank* ControlledTank = GetControlledTank();

	if (ensure(ControlledTank))
	{
		// aim towards the player tank
		ATank* PlayerTank = GetPlayerTank();

		// move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		if (ensure(PlayerTank))
		{
			ControlledTank->AimAt(PlayerTank->GetActorLocation());

			ControlledTank->Fire();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController failed to GET the player tank!"));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	ensure(GetPawn() != nullptr);

	ATank* AITank = Cast<ATank>(GetPawn());

	return AITank;
}

ATank* ATankAIController::GetPlayerTank() const
{
	ensure(GetWorld() != nullptr);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	ATank* PlayerTank = nullptr;

	if (ensure(PlayerController))
	{
		PlayerTank = Cast<ATank>(PlayerController->GetPawn());
	}

	return PlayerTank;
}


