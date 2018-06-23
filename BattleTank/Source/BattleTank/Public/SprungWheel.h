// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"

#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMegnitute);

private:

	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent * Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent * Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent * PhysicsConstraintComp = nullptr;

	// Constraint between the axle and the wheel
	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent * WheelConstraintComp = nullptr;

	// Total force of this frame
	float ForceMegnitute = 0;
};
