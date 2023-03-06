// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveActorComponent.h"

// Sets default values
AMoveActorComponent::AMoveActorComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMoveActorComponent::BeginPlay()
{
	Super::BeginPlay();
	FString ActorName = GetOwner()->GetActorNameOrLabel();
	FString PositionOfObject = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("Actor %s is at location %s"), *ActorName, *PositionOfObject);
	UE_LOG(LogTemp, Warning, TEXT("Actor %s is at x: %f, y: %f"), *ActorName, GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y);
	StartLocation = GetOwner()->GetActorLocation();
}

// Called every frame
void AMoveActorComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveActor(DeltaTime);
}

void AMoveActorComponent::MoveActor(float DeltaTime)
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	CurrentLocation = CurrentLocation + MoveVelocity * DeltaTime;
	GetOwner()->SetActorLocation(CurrentLocation);
	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
	if (DistanceMoved >= MoveDistance)
	{
		FVector MoveDirection = MoveVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		GetOwner()->SetActorLocation(StartLocation);
		MoveVelocity = -MoveVelocity;
	}
}

void AMoveActorComponent::RotateActor(float DeltaTime)
{
	GetOwner()->AddActorLocalRotation(RotationVelocity * DeltaTime);
}

