// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Name of the Actor owner of this component.
	FString PawnName;

	// Player location, rotation, and reach
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	FVector	LineTraceEnd;	// The end of this line determines the maximum reach for the player

	// How far ahead of the player can we reach in centimeters.
	float Reach{ 100.f };

	UPhysicsHandleComponent* PhysicsHandle{ nullptr };
	UInputComponent* InputComponent{ nullptr };

	// Find (assumed) attached physics handle
	void FindPhysicsHandleComponent();
	// Setup (assumed) attached input Component
	void SetupInputComponent();

	// Figures out the player view point and reach at a given time
	void CalculatePlayerViewpointAndReach();

	// Return hit for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach() const;

	// Ray-cast and grab what's in reach.
	void Grab();
	// Called when grab	is released.
	void Release();
};
