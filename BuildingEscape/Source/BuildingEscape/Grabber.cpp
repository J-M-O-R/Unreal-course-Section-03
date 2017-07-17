// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT	// This macro does nothing, the instructor doesn't like to pass parameters by reference, so he wants to mark them.

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// Reporting for duty
	FString PawnName{ GetOwner()->GetName() };
	UE_LOG(LogTemp, Warning, TEXT("%s's grabber reporting for duty!"), *PawnName);
	// Getting the player controler
	
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player view point
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"),
		   *PlayerViewPointLocation.ToString(),
		   *PlayerViewPointRotation.ToString()
	)
}

