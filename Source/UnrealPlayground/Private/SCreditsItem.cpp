// Fill out your copyright notice in the Description page of Project Settings.


#include "SCreditsItem.h"

#include "SCreditsComponent.h"
#include "GameFramework/PlayerState.h"


ASCreditsItem::ASCreditsItem()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = MeshComp;
}

void ASCreditsItem::Show()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void ASCreditsItem::Hide()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void ASCreditsItem::Interact_Implementation(APawn* InstigatorPawn)
{
	USCreditsComponent* CreditsComp = USCreditsComponent::GetCredits(InstigatorPawn->GetPlayerState());
	if (CreditsComp && CreditsComp->ApplyCreditsChange(CreditsChange))
	{
		OnCreditsChangeApplied(InstigatorPawn);

		Hide();

		FTimerHandle Show_TimeHandle;
		GetWorldTimerManager().SetTimer(Show_TimeHandle, this, &ASCreditsItem::Show, RespawnTimeout);
	}
}

void ASCreditsItem::OnCreditsChangeApplied_Implementation(APawn* InstigatorPawn)
{
}
