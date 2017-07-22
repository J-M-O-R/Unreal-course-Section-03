// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


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

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//UPROPERTY(VisibleAnywhere)	<- Just shows the field, not allowing editing.
	UPROPERTY(EditAnywhere)
	float OpenAngle = 110.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate =	nullptr;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;

	float LastDoorOpenTime;
	/**** Udemy course:
	AActor* Owner;	// The owning door.
	****/
	AActor* Owner{ GetOwner() };	// The owning door.
	/* Removed in lecture 88, so now the doors will be open by any Actor
	AActor* ActorThatOpens;
	*/
	// Returns total mass in kg
	float GetTotalMassOfActorsOnPlate();
};
