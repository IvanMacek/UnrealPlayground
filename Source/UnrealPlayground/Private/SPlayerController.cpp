// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerController.h"

#include "SPlayerState.h"

void ASPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	OnPawnChanged.Broadcast(InPawn);
}

void ASPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ASPlayerState* MyPlayerState = Cast<ASPlayerState>(PlayerState);
	if (ensure(MyPlayerState))
	{
		OnPlayerStateChanged.Broadcast(MyPlayerState);
	}
}
