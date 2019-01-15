// Copyright ADVANCED Co.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

//#include "PlayerUI.h"
//#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
//#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
//#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"
#include <assert.h>

//#define DEBUG_LINE
#ifdef DEBUG_LINE
#include "DrawDebugHelpers.h"
#endif


ATankPlayerController::ATankPlayerController()
{
	//SetupUI();

	// Set this controller to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

//void ATankPlayerController::SetupUI()
//{
	////// .cpp constructor
	//ConstructorHelpers::FClassFinder<UUserWidget> PlayerUIClassFinder(TEXT("/Game/GUI/PlayerUI_BP"));

	//if (PlayerUIClassFinder.Succeeded())
	//{
	//	m_PlayerUIClass = PlayerUIClassFinder.Class;
	//}
//}

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	APawn* ControlledTank = GetControlledTank();

	if (ensure(ControlledTank))
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

	if (ensure(ControlledTank))
	{
		UTankAimingComponent* TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

		if (ensure(TankAimingComponent))
		{
			// broadcast event FoundAimingComponent
			FoundAimingComponent(TankAimingComponent);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("TankPlayerController can not find TankAimingComponent at Begin Play!"));
		}
	}
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

	//UE_LOG(LogTemp, Warning, TEXT("TankPlayerController HitLocation: %s"), *HitLocation.ToString);

	// get world locaton of linetrace through crosshair
	FVector OutHitLocation;
	if (CalcSightRayHitLocation(OutHitLocation))
	{
		UTankAimingComponent* TankAimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

		if (ensure(TankAimingComponent))
		{
			TankAimingComponent->AimAt(OutHitLocation);
		}
	}
}

bool ATankPlayerController::CalcSightRayHitLocation(FVector& OutHitLocation) const
{
	ensure(GetWorld() != nullptr);
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

	// compute the screen position of the crosshair
	int32 ViewportX = 0, ViewportY = 0;
	GetViewportSize(ViewportX, ViewportY);
	FVector2D CrosshairScreenPos = FVector2D(ViewportX * CrosshairXFactor, ViewportY * CrosshairYFactor);

	//UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Crosshair screen pos: %s"), *(CrosshairScreenPos.ToString()));

	// de-project the screen position of the crosshair in a world position
	FVector CameraWorldPos, CameraWorldDir;
	if (DeprojectScreenPositionToWorld(CrosshairScreenPos.X, CrosshairScreenPos.Y, CameraWorldPos, CameraWorldDir))
	{
		//UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Camera world - pos: %s, dir: %s"), *(CameraWorldPos.ToString()), *(CameraWorldDir.ToString()));

		// Line-trace (AKA Ray-cast) out to reach distance
		FHitResult LineTraceHitOut;
		FVector LineStart = PlayerCameraManager->GetCameraLocation();
		FVector LineEnd = LineStart + CameraWorldDir * LineTraceRange;
		if (GetWorld()->LineTraceSingleByChannel(LineTraceHitOut,
			LineStart,
			LineEnd,
			ECollisionChannel::ECC_Visibility
		))
		{
			OutHitLocation = LineTraceHitOut.ImpactPoint;

#ifdef DEBUG_LINE
			/// Draw a red trace in the world, to visualize
			DrawDebugLine(GetWorld(),
				LineStart,
				LineEnd,
				FColor::Red,
				false,
				-1.0f,
				0,
				3.0f);
#endif


			//UE_LOG(LogTemp, Warning, TEXT("TankPlayerController we hit something: %s"), *(OutHitLocation.ToString()));

			return true;
		}
		else
		{
			OutHitLocation = FVector(0.0f);

			//UE_LOG(LogTemp, Warning, TEXT("TankPlayerController we missed: %s"), *(OutHitLocation.ToString()));
		}
	}

	return false;
}

APawn* ATankPlayerController::GetControlledTank() const
{
	//UE_LOG(LogTemp, Warning, TEXT("C++ : TANK PLAYER CONTROLLER - GetControlledTank"), *GetName());

	ensure(GetPawn() != nullptr);

	return GetPawn();
}


