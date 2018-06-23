// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnComponent.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
USpawnComponent::USpawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	// Spawn the SprungWheel object and attach to the component
	auto Object = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *(GetComponentTransform().ToString()));
	if (!ensure(Object)) { return; }

	Object->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(Object, GetComponentTransform());
}


// Called every frame
void USpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

