// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

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

	/* Getting an Actor in a Top-Down search, i.e. from the World to the Player Controler (the mind)
	to its associated Pawn (the body). Remember Pawn inherits from Actor, so its ok the below association:
	Give GetPawn() to AActor.

	In the code commented below we get the Actor Bottom-Up, i.e. from this Component to its associated
	actor -> GetOwner().
	*/

	/**** Udemy course:
	Owner = GetOwner();
	****/
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	/* Getting the Z rotation of the Actor (StaticMeshActor in this case) to wich this Component
	   is associated.
	   And printing the information in the Output Log tab of the Unreal Editor.

	AActor* Owner{ GetOwner() };
	float Zrotation{ Owner->GetActorRotation().GetComponentForAxis(EAxis::Z) };
	UE_LOG(LogTemp, Warning, TEXT("The rotation for the Z axis is %f"), Zrotation);
	*/
}

void UOpenDoor::OpenDoor() {

	// With a Rotator.
	FRotator Rotation1{ 0.f, OpenAngle, 0.f };
	Owner->SetActorRotation(Rotation1);

	/* With a Quaternion.
	FRotator Rotation2{ 0.f, OpenAngle, 0.f };
	FQuat Quaternion{ Rotation2.Quaternion() };
	Owner->SetActorRotation(Quaternion);

	These are absolute angle values. All "SetActorRotation()" does it's to set the values for
	the X, Y, and Z fields of the "Rotation" subsection in the "Transform" section of the
	"Details" window.
	*/
}

void UOpenDoor::CloseDoor() {

	Owner->SetActorRotation(FRotator{ 0.f, 180.f, 0.f });

}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Polling the Trigger Volume every frame and if ActorThatOpen is in the volume then open the door(s).
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() >= LastDoorOpenTime + DoorCloseDelay) {
		CloseDoor();
	}
	
}

