// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"))

	/// LINE TRACE and see if we reach any actors with physics body collision channel set
	GetFirstPhysicsBodyInReach();

	/// If we hit something then attach a physics handle
	// TODO Attach physics handle
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab released"))

	// TODO Release physics handle
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if the physics handle is attached
		// move the object that we're holding

		
		
		
	/*
	The code below was enterely refactored into the function "FHitResult GetFirstPhysicsBodyInReach() const"
	I'm leaving it here to see where code can go.

	/// Get player view point
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

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

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const {

	/// Get player view point
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	FVector	LineTraceEnd{ PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach };

	/// Line-trace (AKA ray-cast) out to reach distance
	FCollisionQueryParams TraceParameters{ FName{ TEXT("") }, false, GetOwner() };
	FHitResult Hit;

	/// LineTraceMultiBy_____ passes through multiple objects and returns different references.
	bool Hitted{ GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams{ ECollisionChannel::ECC_PhysicsBody },
		TraceParameters
	) };
	if (Hitted) {
		FString ReachedActor{ Hit.GetActor()->GetName() };
		UE_LOG(LogTemp, Warning, TEXT("%s is at reaching distance!"), *ReachedActor)
	}

	return FHitResult();
}