// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveActorComponent.generated.h"

UCLASS()
class NEWPROJECT_API AMoveActorComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveActorComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveActor(float DeltaTime);
	void RotateActor(float DeltaTime);

private:
	UPROPERTY(EditAnywhere, Category = "Move Actor Component")
		FVector MoveVelocity = FVector(100, 0, 0);
	UPROPERTY(VisibleAnywhere, Category = "Move Actor Component")
		FVector StartLocation;
	UPROPERTY(EditAnywhere, Category = "Move Actor Component")
		float MoveDistance = 100;
	UPROPERTY(EditAnywhere, Category = "Move Actor Component");
		FRotator RotationVelocity;
};
