// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

#define OUT	// This macro does nothing, the instructor doesn't like to pass parameters by reference, so he wants to mark them.

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PawnName = GetOwner()->GetName();
	/*
	// Reporting for duty
	UE_LOG(LogTemp, Warning, TEXT("%s's grabber reporting for duty!"), *PawnName);
	*/
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

/// Look for attached Physics Handle component
void UGrabber::FindPhysicsHandleComponent() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("%s missing Physics Handle Component"), *PawnName)
	}
}

// Look for attached Input component (only appears at run time)
void UGrabber::SetupInputComponent() {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s missing Input Component"), *PawnName)
	}
}

void UGrabber::Grab() {
	/// LINE TRACE and see if we reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ActorHit{ HitResult.GetActor() };
	auto ComponentToGrab{ HitResult.GetComponent() };

	/// If we hit something then attach a physics handle
	if (ActorHit) {
		// Attach physics handle
		PhysicsHandle->GrabComponent(
			ComponentToGrab,	// Gets the mesh in our case
			NAME_None,	// No bones needed
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true	// Allow rotation
		);
	}

}

void UGrabber::Release() {
		// Release physics handle
		PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	/*
	Update the location and reach of the player. We need it to update the location of the current reach (LineTraceEnd)
	of the player to be able to move the object that we are holding (if any).
	*/
	CalculatePlayerViewpointAndReach();

	// if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent) {
		// move the object that we're holding. Holding it at the end of the player's reach.
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
		
	/*
	The code below was enterely refactored into the function "FHitResult GetFirstPhysicsBodyInReach() const"
	I'm leaving it here to see where code can go.

	/// Get player view point
	CalculatePlayerViewpointAndReach();

	The code below just output the x, y, z coordinates of the position of the player, and the roll, pitch, and yaw
	of its rotation:

	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"),
		   *PlayerViewPointLocation.ToString(),
		   *PlayerViewPointRotation.ToString()
	)

	We'll try to draw a line proyecting out of the player instead:
	
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor{ 255, 0, 0 },
		false,
		0.f,
		0.f,
		10.f
	);
	*/
}

void UGrabber::CalculatePlayerViewpointAndReach() {
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const {
	/// Line-trace (AKA ray-cast) out to reach distance
	FCollisionQueryParams TraceParameters{ FName{ TEXT("") }, false, GetOwner() };
	FHitResult HitResult;

	/// LineTraceMultiBy_____ passes through multiple objects and returns different references.
	bool Hitted{ GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams{ ECollisionChannel::ECC_PhysicsBody },
		TraceParameters
	) };
	// Udemy's instructor, at lesson 87, said we don't need to check for this (Hitted) anymore.
	// I don't know why, so I'm leaving it.
	if (Hitted) {
		FString ReachedActor{ HitResult.GetActor()->GetName() };
		UE_LOG(LogTemp, Warning, TEXT("%s is at reaching distance!"), *ReachedActor)
	}
	return HitResult;
}