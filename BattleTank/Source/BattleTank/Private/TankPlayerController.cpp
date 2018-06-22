// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(GetPawn()->FindComponentByClass<UTankAimingComponent>());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair() {
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation)) {
		// If it hits the landscape
		// Tell controlled tank to aim at this point
		AimingComponent->AimAt(HitLocation);
	}
}

// Get world location if linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the corsshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	// "De-project" the screen position to a world position
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Raycast the hit object from this world position
		// if hit something, update the location and return true
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector WorldLocation, WorldDirection;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation,
		LookDirection // only thing we need
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
	    /*const FCollisionQueryParams & Params,
	    const FCollisionResponseParams & ResponseParam*/
	) {
		HitLocation = HitResult.Location;
		return true;
	}
	else {
		HitLocation = FVector(0);
		return false;
	}

}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}


