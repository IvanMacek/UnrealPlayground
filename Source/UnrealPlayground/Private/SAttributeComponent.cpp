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
	Health = FMath::Clamp(Health + Delta, 0.f, HealthMax);

	OnHealthChanged.Broadcast(Instigator, this, Health, Delta);

	return true;
}

bool USAttributeComponent::IsMaxHealth() const
{
	return Health == HealthMax;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.f;
}
