// Fill out your copyright notice in the Description page of Project Settings.

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

	auto ControlledTank = GetControlledTank();

	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController possesing %s"), *(ControlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not possesing a tank!"));
	}

	auto PlayerTank = GetPlayerTank();

	if (PlayerTank)
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

	if (ControlledTank)
	{
		// TODO move towards the player

		// aim towards the player tank
		ATank* PlayerTank = GetPlayerTank();

		if (PlayerTank)
		{
			ControlledTank->AimAt(PlayerTank->GetActorLocation());

			ControlledTank->Fire(); //TODO
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController failed to GET the player tank!"));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	assert(GetPawn() != nullptr);

	ATank* AITank = Cast<ATank>(GetPawn());

	return AITank;
}

ATank* ATankAIController::GetPlayerTank() const
{
	assert(GetWorld() != nullptr);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	ATank* PlayerTank = nullptr;

	if (PlayerController)
	{
		PlayerTank = Cast<ATank>(PlayerController->GetPawn());
	}

	return PlayerTank;
}


