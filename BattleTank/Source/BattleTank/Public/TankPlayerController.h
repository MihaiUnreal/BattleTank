// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "TankPlayerController.generated.h" // must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankPlayerController();


private:
	void SetupUI();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// start the tank moving the barrel so that a shot would hit where
	// the corsshair intersects the world
	void AimTowardsCrosshair();

	bool CalcSightRayHitLocation(FVector& OutHitLocation) const;

	ATank* GetControlledTank() const;

	//TSubclassOf<class UUserWidget> m_PlayerUIClass;
	//UWidget* m_CrosshairWidget = nullptr;
};
