#include "EnemyCharacter.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "DodgeballProjectile.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SightSource = CreateDefaultSubobject<USceneComponent>(TEXT("Sight Source"));
	SightSource->SetupAttachment(RootComponent);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	bCanSeePlayer = LookAtActor(PlayerCharacter);

	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePlayer)
		{
			GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, &AEnemyCharacter::ThrowDodgeball, ThrowingInterval, true, ThrowingDelay);
		}
		else
		{
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}

	bPreviousCanSeePlayer = bCanSeePlayer;
}

bool AEnemyCharacter::LookAtActor(AActor* TargetActor)
{
	if (TargetActor == nullptr) return false;

	if (CanSeeActor(TargetActor))
	{
		FVector Start = GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);
		SetActorRotation(LookAtRotation);
		return true;
	}

	return false;
}

bool AEnemyCharacter::CanSeeActor(AActor* TargetActor)
{
	if (TargetActor == nullptr) return false;
	FHitResult Hit;
	FVector Start = SightSource->GetComponentLocation();
	FVector End = TargetActor->GetActorLocation();
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(TargetActor);
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	return !Hit.bBlockingHit;
}

void AEnemyCharacter::ThrowDodgeball()
{
	if (DodgeballClass == nullptr)
	{
		return;
	}

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	GetWorld()->SpawnActor<ADodgeballProjectile>(DodgeballClass, SpawnLocation, GetActorRotation());
}