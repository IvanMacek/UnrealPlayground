// Fill out your copyright notice in the Description page of Project Settings.


#include "SCreditsItem.h"

#include "SCreditsComponent.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"


ASCreditsItem::ASCreditsItem()
{
	bReplicates = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = MeshComp;
}

void ASCreditsItem::OnRep_Visible()
{
	SetActorHiddenInGame(!bVisible);
	SetActorEnableCollision(bVisible);
}

void ASCreditsItem::Show()
{
	bVisible = true;
	OnRep_Visible();
}

void ASCreditsItem::Hide()
{
	bVisible = false;
	OnRep_Visible();
}

void ASCreditsItem::Interact_Implementation(APawn* InstigatorPawn)
{
	if (HasAuthority())
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
}

void ASCreditsItem::OnCreditsChangeApplied_Implementation(APawn* InstigatorPawn)
{
}

void ASCreditsItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASCreditsItem, bVisible);
}
