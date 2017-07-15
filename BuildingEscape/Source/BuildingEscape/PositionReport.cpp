// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "PositionReport.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName{ GetOwner()->GetName() };
	FString ObjectPos1{ GetOwner()->GetActorLocation().ToString() };
	// Or another way (the one used in the course).
	FString ObjectPos2{ GetOwner()->GetTransform().GetLocation().ToString() };
	UE_LOG(LogTemp, Warning, TEXT("%s is at (from Pos1) %s - (from Pos2) %s"), *ObjectName, *ObjectPos1, *ObjectPos2);
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

