// Fill out your copyright notice in the Description page of Project Settings.


#include "FShootingComponent.h"

// Sets default values for this component's properties
UFShootingComponent::UFShootingComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}


void UFShootingComponent::BeginPlay()
{
	Super::BeginPlay();


}



void UFShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

