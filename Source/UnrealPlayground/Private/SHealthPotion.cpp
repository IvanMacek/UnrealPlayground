// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "SAttributeComponent.h"
#include "GameFramework/PlayerState.h"

ASHealthPotion::ASHealthPotion()
{
	CreditsChange = -30;
}

void ASHealthPotion::OnCreditsChangeApplied_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* InstigatorAttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	if (InstigatorAttributeComp)
	{
		if (!InstigatorAttributeComp->IsMaxHealth())
		{
			InstigatorAttributeComp->ApplyHealthChange(this, HealingAmount);
		}
	}
}
