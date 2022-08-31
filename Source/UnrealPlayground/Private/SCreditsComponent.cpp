// Fill out your copyright notice in the Description page of Project Settings.


#include "SCreditsComponent.h"

#include "Net/UnrealNetwork.h"


USCreditsComponent::USCreditsComponent()
{
	SetIsReplicatedByDefault(true);
}

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

	if (GetOwner()->HasAuthority())
	{
		const int32 OldCredits = Credits;

		Credits += Delta;
		OnRep_Credits(OldCredits);
	}

	return true;
}

void USCreditsComponent::OnRep_Credits(int32 OldCredits)
{
	OnCreditsChanged.Broadcast(this, Credits, Credits - OldCredits);
}

void USCreditsComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USCreditsComponent, Credits);
}
