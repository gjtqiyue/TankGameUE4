// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"



// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Take damage
float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoint = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoint, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0) {
		OnDeath.Broadcast();
	}

	return DamageToApply;
}

float ATank::GetHealthPercent()
{
	return (float)CurrentHealth / (float)MaxHealth;
}
