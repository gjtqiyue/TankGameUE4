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
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
//{
//	Barrel = BarrelToSet;
//	AimingComponent->SetBarrelReference(BarrelToSet);
//}
//
//void ATank::SetTurretReference(UTankTurret * TurretToSet)
//{
//	AimingComponent->SetTurretReference(TurretToSet);
//}

//void ATank::Fire()
//{
//	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
//
//	if (!ensure(ProjectileBlueprint)) { return; }
//	if (AimingComponent->BarrelReference() && isReloaded && canFire) {
//		UE_LOG(LogTemp, Warning, TEXT("Fire"));
//		// Spawn a projectile at the spawn point
//		FTransform SpawnPoint = AimingComponent->BarrelReference()->GetSocketTransform(FName("Projectile"));
//		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnPoint);
//
//		Projectile->LaunchProjectile(LaunchSpeed);
//
//		// Reset the last fire time
//		LastFireTime = FPlatformTime::Seconds();
//	}
//}
