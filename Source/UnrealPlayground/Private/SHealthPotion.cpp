// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "SAttributeComponent.h"
#include "GameFramework/PlayerState.h"

#define LOCTEXT_NAMESPACE "InteractableActors"

ASHealthPotion::ASHealthPotion()
{
	CreditsChange = -30;
}

void ASHealthPotion::OnCreditsChangeApplied_Implementation(APawn* InstigatorPawn)
{
	if (USAttributeComponent* InstigatorAttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn))
	{
		if (!InstigatorAttributeComp->IsMaxHealth())
		{
			InstigatorAttributeComp->ApplyHealthChange(this, HealingAmount);
		}
	}
}

FText ASHealthPotion::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	if (const USAttributeComponent* InstigatorAttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn))
	{
		if (InstigatorAttributeComp->IsMaxHealth())
		{
			return LOCTEXT("HealthPotion_FullHealthWarning", "Already at full health.");
		}
	}

	return FText::Format(LOCTEXT("HealthPotion_InteractMessage", "Cost {0} Credits. Restores health."), CreditsChange);
}

#undef LOCTEXT_NAMESPACE
