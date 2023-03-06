#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class NEWPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LookAt, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SightSource;

public:

	AEnemyCharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	bool LookAtActor(AActor* TargetActor);
	bool CanSeeActor(AActor* TargetActor);

	void ThrowDodgeball();
	bool bCanSeePlayer = false;
	bool bPreviousCanSeePlayer = false;

	FTimerHandle ThrowTimerHandle;

	float ThrowingInterval = 2.f;
	float ThrowingDelay = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Dodgeball)
		TSubclassOf<class ADodgeballProjectile> DodgeballClass;
};