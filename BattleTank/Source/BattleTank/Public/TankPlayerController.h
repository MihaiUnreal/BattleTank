// Copyright ADVANCED Co.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "TankPlayerController.generated.h" // must be the last include

class ATank;
class UTankAimingComponent;

/**
 * Responsible for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankPlayerController();

protected:
	UFUNCTION(BlueprintCallable, Category = Setup)
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	//void SetupUI();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// start the tank moving the barrel so that a shot would hit where
	// the corsshair intersects the world
	void AimTowardsCrosshair();

	bool CalcSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXFactor = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYFactor = 0.333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;

	//TSubclassOf<class UUserWidget> m_PlayerUIClass;
	//UWidget* m_CrosshairWidget = nullptr;
};
