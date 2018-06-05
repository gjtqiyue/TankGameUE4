// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Hold Tank Barrel's property and Elevate method
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// clamp between -1 and 1
	// -1 minSpeed and +1 maxSpeed
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSec = 20; // Sensible default
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegree = 30;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegree = 0;
};
