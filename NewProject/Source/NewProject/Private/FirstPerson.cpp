// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPerson.h"

// Sets default values
AFirstPerson::AFirstPerson()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFirstPerson::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirstPerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFirstPerson::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFirstPerson::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFirstPerson::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AFirstPerson::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("Lookup"), this, &AFirstPerson::AddControllerPitchInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AFirstPerson::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AFirstPerson::StopJumping);
}

void AFirstPerson::MoveForward(float AxisVal)
{
	AddMovementInput(GetActorForwardVector() * AxisVal);
}

void AFirstPerson::MoveRight(float AxisVal)
{
	AddMovementInput(GetActorRightVector() * AxisVal);
}