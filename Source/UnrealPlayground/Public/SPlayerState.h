// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCreditsComponent.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"


UCLASS()
class UNREALPLAYGROUND_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASPlayerState();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USCreditsComponent* CreditsComp;
};
