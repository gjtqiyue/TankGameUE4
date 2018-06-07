// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CoreMinimal.h"
#include "Tank.generated.h"

// Forward declaration
class UTankBarrel;
class UTankTurret;
class UTankTrack;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	// Sets default values for this pawn's properties
	ATank();

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = TankAction)
	void Fire();

protected:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel * BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret * TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTrackReference(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet);

private:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UTankAimingComponent * AimingComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 10000; // Sensible starting value of 1000m/s

	// Get a reference of the ProjectileBlueprint so we can spawn it
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditAnywhere, Category = Firing)
	bool canFire = true;

	// Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	UTankTrack * LeftTrack = nullptr;

	UTankTrack * RightTrack = nullptr;

	double LastFireTime = 0;
};
