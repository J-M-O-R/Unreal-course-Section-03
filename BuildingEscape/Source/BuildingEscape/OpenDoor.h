// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
/*
The openning/closing of the door is now do it in the Blueprint(ed) class.
	void OpenDoor();
	void CloseDoor();
*/
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

private:
	/* Now, generating the open/close events to the Blueprint door class, instead of managing them in C++,
	we don't need these variables anymore:

	//UPROPERTY(VisibleAnywhere)	<- Just shows the field, not allowing editing.
	UPROPERTY(EditAnywhere)
	float OpenAngle = 110.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;

	float LastDoorOpenTime;
	*/

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	/**** Udemy course:
	AActor* Owner;	// The owning door.
	****/
	AActor* Owner{ GetOwner() };	// The owning door.
	/* Removed in lecture 88, so now the doors will be open by any Actor
	AActor* ActorThatOpens;
	*/

	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.f;

	// Returns total mass in kg
	float GetTotalMassOfActorsOnPlate();
};
