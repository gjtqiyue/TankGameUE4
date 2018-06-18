// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStaticsTypes.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	// Reset the last fire time
	LastFireTime = FPlatformTime::Seconds();
	CurrentAmmo = MaxAmmo;
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentAmmo <= 0) {
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
		FiringStatus = EFiringStatus::Reload;
	}
	else if (isBarrelMoving()) {
		FiringStatus = EFiringStatus::Aim;
	}
	else {
		FiringStatus = EFiringStatus::Locked;
	}
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the outlaunchvelocity
	bool bHaveSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("NoSolutionFound"));
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	// Find the difference between two directions
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotation;

	//UE_LOG(LogTemp, Warning, TEXT("%f"), DeltaRotator.Yaw);
	float angle = DeltaRotator.Yaw;
	if (DeltaRotator.Yaw >= 180) {
		angle = DeltaRotator.Yaw - 360;
	}
	if (DeltaRotator.Yaw <= -180) {
		angle = DeltaRotator.Yaw + 360;
	}

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(angle);
	
}

bool UTankAimingComponent::isBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	FVector CurrentRotation = Barrel->GetForwardVector();
	FVector ExpectedRotation = AimDirection;
	if (CurrentRotation.Equals(ExpectedRotation, 0.01f) ) {
		return false;
	}
	else {
		return true;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::Fire()
{
	
	if (FiringStatus != EFiringStatus::Reload && canFire && FiringStatus != EFiringStatus::OutOfAmmo) {
		if (!ensure(ProjectileBlueprint)) { return; }
		if (!ensure(Barrel)) { return; }
		UE_LOG(LogTemp, Warning, TEXT("Fire"));
		// Spawn a projectile at the spawn point
		FTransform SpawnPoint = Barrel->GetSocketTransform(FName("Projectile"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnPoint);

		Projectile->LaunchProjectile(LaunchSpeed);

		CurrentAmmo = CurrentAmmo - 1;

		LastFireTime = FPlatformTime::Seconds();
	}
}

EFiringStatus UTankAimingComponent::getFiringStatus() const
{
	return FiringStatus;
}
