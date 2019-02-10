// Copyright ADVANCED Co.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UStaticMeshComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	void LaunchProjectile(float Speed);

protected:
	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* CollisionMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UParticleSystemComponent* LaunchBlastComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UParticleSystemComponent* ImpactBlastComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	URadialForceComponent* ExplosionForceComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float DestroyDelay = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float ProjectileDamage = 5.0f;

	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void OnTimerTrigger();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
