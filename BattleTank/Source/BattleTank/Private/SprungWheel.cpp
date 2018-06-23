// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PhysicsConstraintComp = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring Constraint"));
	SetRootComponent(PhysicsConstraintComp);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->AttachTo(PhysicsConstraintComp);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->AttachTo(Axle);

	WheelConstraintComp = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Wheel Constraint"));
	WheelConstraintComp->AttachTo(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	// Set up the constraint component
	if (ensure(GetAttachParentActor())) {
		UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		PhysicsConstraintComp->SetConstrainedComponents(
			BodyRoot,
			NAME_None,
			Axle,
			NAME_None
		);
		WheelConstraintComp->SetConstrainedComponents(
			Axle,
			NAME_None,
			Wheel,
			NAME_None
		);
	}

}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

