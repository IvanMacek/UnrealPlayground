// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

USAttributeComponent* USAttributeComponent::GetAttributes(const AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(StaticClass()));
	}

	return nullptr;
}

bool USAttributeComponent::IsActorAlive(const AActor* Actor)
{
	const USAttributeComponent* AttributeComp = GetAttributes(Actor);
	return AttributeComp != nullptr && AttributeComp->IsAlive();
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, const float Delta)
{
	Health = FMath::Clamp(Health + Delta, 0.f, HealthMax);

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, Delta);

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

bool USAttributeComponent::IsLowHealth() const
{
	return Health <= (HealthMax * 0.25f);
}

float USAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}
