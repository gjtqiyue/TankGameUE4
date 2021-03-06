// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/RadialForceComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void LaunchProjectile(float LaunchSpeed);

private:
	UProjectileMovementComponent * ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent * CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UParticleSystemComponent * LaunchBlast = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = Components)
	UParticleSystemComponent * ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	URadialForceComponent * ExplosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Delay)
	float DestroyDelay = 10;

	UPROPERTY(EditDefaultsOnly, Category = Damage)
	float BaseDamage = 20;

	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);
	
	void OnTimerExpire();
};
