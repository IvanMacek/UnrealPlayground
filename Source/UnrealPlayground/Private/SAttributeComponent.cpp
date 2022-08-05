// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
}

// Called when the game starts
void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool USAttributeComponent::ApplyHealthChange(AActor* Instigator, float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(Instigator, this, Health, Delta);

	return true;
}
