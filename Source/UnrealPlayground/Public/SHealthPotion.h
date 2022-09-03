// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCreditsItem.h"
#include "SHealthPotion.generated.h"

UCLASS()
class UNREALPLAYGROUND_API ASHealthPotion : public ASCreditsItem
{
	GENERATED_BODY()
	
public:
	ASHealthPotion();

	virtual void OnCreditsChangeApplied_Implementation(APawn* InstigatorPawn) override;

	virtual FText GetInteractText_Implementation(APawn* InstigatorPawn) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float HealingAmount = 20.f;
};
