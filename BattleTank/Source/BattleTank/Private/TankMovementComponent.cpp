// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TankTrack.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"



void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto TankIntention = MoveVelocity.GetSafeNormal();

	float IntendForward = FVector::DotProduct(TankForward, TankIntention);
	float IntendRight = FVector::CrossProduct(TankForward, TankIntention).Z;

	//UE_LOG(LogTemp, Warning, TEXT("IntendForward: %f, IntendRight: %f"), IntendForward, IntendRight);
	IntendMoveForward(IntendForward);
	IntendTurnRight(IntendRight);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}
