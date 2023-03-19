#include "DodgeballProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TopDownCharacter.h"
#include "Kismet/GameplayStatics.h"

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

	ATopDownCharacter* Player = Cast<ATopDownCharacter>(OtherActor);

	if (Player != nullptr)
	{
		if (HitParticles != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorTransform());
		}
		if (DamageSound != nullptr && NormalImpulse.Size() > 1000.0f)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetActorLocation(), 1.0f, FMath::RandRange(0.7f, 1.3f), 0.0f, BounceSoundAttenuation);
		}
		Destroy();
	}
	else if (BounceSound != nullptr && NormalImpulse.Size() > 1000.0f)
	{
		UGameplayStatics::PlaySoundAtLocation(this, BounceSound, GetActorLocation(), 1.0f, FMath::RandRange(0.7f, 1.3f), 0.0f, BounceSoundAttenuation);
	}
}