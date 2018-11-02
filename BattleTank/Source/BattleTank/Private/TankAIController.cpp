// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include <assert.h>

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

ATank* ATankAIController::GetControlledTank() const
{
	assert(GetPawn() != nullptr);

	ATank* AITank = Cast<ATank>(GetPawn());

	return AITank;
}

ATank * ATankAIController::GetPlayerTank() const
{
	assert(GetWorld() != nullptr);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	ATank* PlayerTank = nullptr;

	if (PlayerController)
	{
		assert(GetPawn() != nullptr);

		PlayerTank = Cast<ATank>(PlayerController->GetPawn());
	}

	return PlayerTank;
}


