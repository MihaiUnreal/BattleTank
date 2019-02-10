// Copyright ADVANCED Co.

#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Colission Mesh Component"));
	if (ensure(CollisionMeshComponent))
	{
		SetRootComponent(CollisionMeshComponent);
		CollisionMeshComponent->SetNotifyRigidBodyCollision(true);
		CollisionMeshComponent->SetVisibility(false);
	}

	LaunchBlastComponent = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast Component"));
	if (ensure(LaunchBlastComponent))
	{
		LaunchBlastComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

	ImpactBlastComponent = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast Component"));
	if (ensure(ImpactBlastComponent))
	{
		ImpactBlastComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		// no impact blast at startup
		ImpactBlastComponent->SetAutoActivate(false);
	}

	ExplosionForceComponent = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force Component"));
	if (ensure(ExplosionForceComponent))
	{
		ExplosionForceComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		// no explosion force at startup
		ExplosionForceComponent->SetAutoActivate(false);
	}

	// create the ProjectileMovementComponent (as child of Tank)
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	if (ensure(ProjectileMovementComponent))
	{
		ProjectileMovementComponent->SetAutoActivate(false);
	}
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// register on hit delegate
	if (ensure(CollisionMeshComponent))
	{
		CollisionMeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called every frame
void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT(" OnHit!"));

	if (ensure(LaunchBlastComponent))
	{
		LaunchBlastComponent->Deactivate();
	}

	if (ensure(ImpactBlastComponent))
	{
		ImpactBlastComponent->Activate();
	}

	if (ensure(ExplosionForceComponent))
	{
		ExplosionForceComponent->FireImpulse();
	}

	// Destroy the projectile after some time
// set impact blast component to be the root as the static mesh
// is gonna be deleted
	if (ensure(ImpactBlastComponent) && ensure(CollisionMeshComponent))
	{
		SetRootComponent(ImpactBlastComponent);
		CollisionMeshComponent->DestroyComponent();
	}


	if (ensure(ExplosionForceComponent))
	{
		bool isHit = UGameplayStatics::ApplyRadialDamage(
			this,
			ProjectileDamage,
			GetActorLocation(),
			ExplosionForceComponent->Radius,
			UDamageType::StaticClass(),
			TArray<AActor*>() // damage all actors within the radius
		);

		if (isHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("OnHit: we have at least 1 hit with %f damage!"), ProjectileDamage);
		}
	}

	if (ensure(GetWorld()))
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::OnTimerTrigger, DestroyDelay);
	}
}

void AProjectile::OnTimerTrigger()
{
	// on timer out destroy the projectile actor irself
	Destroy();
}

void AProjectile::LaunchProjectile(float Speed)
{
	ensure(GetWorld() != nullptr);

	float Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f : Projectile fires at %f !"), Time, Speed);

	if (ensure(ProjectileMovementComponent))
	{
		ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
		ProjectileMovementComponent->Activate();
	}
}
