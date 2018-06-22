// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// How close AI tank can get to player
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float AcceptanceRadius = 8000;

	UFUNCTION()
	void OnTankDeath();
	
private:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	UTankAimingComponent * AimingComponent = nullptr;
};
