// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "SprungWheel.h"
#include "SpawnComponent.h"


// Sets default values for this component's properties
UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	
	
}


void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float Throttle)
{
	// Clamp the actual throttle value
	auto ForceApplied = Throttle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();

	// iterate every single wheel
	for (ASprungWheel* Wheel : Wheels) {
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children) {
		auto SpawnPoint = Cast<USpawnComponent>(Child);
		if (!ensure(SpawnPoint)) { continue; }

		ASprungWheel* SprungWheel = Cast<ASprungWheel>(SpawnPoint->GetSpawnedActor());
		if (ensure(SprungWheel)) {
			ResultArray.Add(SprungWheel);
		}
	}
	return ResultArray;
}





