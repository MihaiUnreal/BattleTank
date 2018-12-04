// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"
#include <assert.h>

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// create the ProjectileMovementComponent (as child of Tank)
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));

	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->bAutoActivate = false;
	}
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	assert(GetWorld() != nullptr);

	float Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f : Projectile fires at %f !"), Time, Speed);

	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
		ProjectileMovementComponent->Activate();
	}
}
