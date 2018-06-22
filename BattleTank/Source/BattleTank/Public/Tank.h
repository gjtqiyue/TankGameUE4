// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CoreMinimal.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankEvent);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	// Sets default values for this pawn's properties
	ATank();

public:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);

	// Return current health
	UFUNCTION(BlueprintPure, Category = Health)
	float GetHealthPercent();

	FTankEvent OnDeath;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Health)
	int32 MaxHealth = 100;

private:
	UPROPERTY(VisibleAnywhere, Category = Health)
	int32 CurrentHealth;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
};
