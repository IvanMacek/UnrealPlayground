// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

#include "SGameModeBase.h"


static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), true, TEXT("Global Damage Modifier for Attribute Component."), ECVF_Cheat);


bool USAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetHealthMax());
}

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

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged())
	{
		return false;
	}

	if (Delta < 0.f)
	{
		const float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();
		Delta *= DamageMultiplier;
	}

	const float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0.f, HealthMax);
	float const ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, Delta);

	if (ActualDelta < 0.f && FMath::IsNearlyZero(Health))
	{
		ASGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASGameModeBase>();
		if (GameMode)
		{
			GameMode->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}

	return !FMath::IsNearlyZero(ActualDelta);
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
