// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "PlayerUI.h"
#include "Engine/World.h"

//#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
//#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
//#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"
#include <assert.h>

ATankPlayerController::ATankPlayerController()
{
	SetupUI();

	// Set this controller to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::SetupUI()
{
	////// .cpp constructor
	//ConstructorHelpers::FClassFinder<UUserWidget> PlayerUIClassFinder(TEXT("/Game/GUI/PlayerUI_BP"));

	//if (PlayerUIClassFinder.Succeeded())
	//{
	//	m_PlayerUIClass = PlayerUIClassFinder.Class;
	//}

}

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();

	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController possesing %s"), *(ControlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController not possesing a tank!"));
	}

	//// beginplay
	//UPlayerUI* PlayerUIWidget = CreateWidget<UPlayerUI>(this, m_PlayerUIClass);

	//if (PlayerUIWidget)
	//{
	//	m_CrosshairWidget = PlayerUIWidget->GetWidgetFromName("AimPoint");
	//}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Aim at crosshair
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	assert(GetControlledTank() != nullptr);

	FVector OutHitLocation;

	//UE_LOG(LogTemp, Warning, TEXT("TankPlayerController HitLocation: %s"), *HitLocation.ToString);

	// get world locaton of linetrace through crosshair
	CalcSightRayHitLocation(OutHitLocation);

	// if it hits tha landscape
		// tell controlled tank to aim at this point
}

bool ATankPlayerController::CalcSightRayHitLocation(FVector& OutHitLocation) const
{
	assert(GetWorld() != nullptr);
	//assert(m_CrosshairWidget != nullptr);

	//FGeometry Geometry = m_CrosshairWidget->GetCachedGeometry();

	//FGeometry Geometry = AimPoint->GetCachedGeometry();
	//FVector2D AbsolutePosition = Geometry.GetAbsolutePosition();
	//UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Crosshair - absolute position: %s"), *(AbsolutePosition.ToString()));

	//UCanvasPanelSlot* CrosshairSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(m_CrosshairWidget);
	//FVector2D ScreenPosition = CrosshairSlot->GetPosition();
	//UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Crosshair slot - position: %s"), *(ScreenPosition.ToString()));

	//FVector WorldPos, WorldDir;
	//DeprojectScreenPositionToWorld(AbsolutePosition.X, AbsolutePosition.Y, WorldPos, WorldDir);
	//UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Crosshair world - pos: %s, dir: %s"), *(WorldPos.ToString()), *(WorldDir.ToString()));

/*
		// Setup query params
		FCollisionQueryParams QueryParams;
		FCollisionResponseParams ResponseParams;

		// Line-trace (AKA Ray-cast) out to reach distance
		FHitResult LineTraceHitOut;
		GetWorld()->LineTraceSingleByChannel(LineTraceHitOut,
			m_PlayerData.ViewPointLocation,
			m_PlayerData.LineTraceEnd,
			ECollisionChannel::ECC_WorldStatic,
			QueryParams,
			ResponseParams
		);
*/

	return false;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	assert(GetPawn() != nullptr);

	ATank* PlayerTank = Cast<ATank>(GetPawn());

	return PlayerTank;
}


