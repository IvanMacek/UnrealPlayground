// Fill out your copyright notice in the Description page of Project Settings.


#include "SCreditsComponent.h"


USCreditsComponent* USCreditsComponent::GetCredits(const AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USCreditsComponent>(FromActor->GetComponentByClass(StaticClass()));
	}

	return nullptr;
}

bool USCreditsComponent::ApplyCreditsChange(const int32 Delta)
{
	if (Credits + Delta < 0)
	{
		return false;
	}

	Credits += Delta;

	OnCreditsChanged.Broadcast(this, Credits, Delta);

	return true;
}
