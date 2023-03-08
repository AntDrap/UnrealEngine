#include "DodgeballProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TopDownCharacter.h"

ADodgeballProjectile::ADodgeballProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComponent->SetSphereRadius(35.f);
	SphereComponent->SetCollisionProfileName(FName("Dodgeball"));
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetNotifyRigidBodyCollision(true);
	SphereComponent->OnComponentHit.AddDynamic(this, &ADodgeballProjectile::OnHit);

	RootComponent = SphereComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 2200.f;
}

void ADodgeballProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(5.f);
}

void ADodgeballProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADodgeballProjectile::OnHit(UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
const FHitResult& Hit)
{
	if (Cast<ATopDownCharacter>(OtherActor) != nullptr)
	{
		Destroy();
	}
}