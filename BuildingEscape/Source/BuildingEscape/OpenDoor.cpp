// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "OpenDoor.h"
#include <GameFramework/Actor.h>

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner{ GetOwner() };
	float Zrotation{ Owner->GetActorRotation().GetComponentForAxis(EAxis::Z) };
	UE_LOG(LogTemp, Warning, TEXT("The rotation for the Z axis is %f"), Zrotation);

	// With a Rotator.
	FRotator Rotation1{ 0.f, 20.f, 0.f };
	Owner->SetActorRotation(Rotation1);

	// With a Quaternion.
	FRotator Rotation2{ 0.f, 30.f, 0.f };
	FQuat Quaternion{ Rotation2.Quaternion() };
	Owner->SetActorRotation(Quaternion);

	/*
	These are absolute angle values. All "SetActorRotation()" does it's to set the values for
	the X, Y, and Z fields of the "Rotation" subsection in the "Transform" section of the
	"Details" window.
	*/
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
