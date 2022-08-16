// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"

#include "Kismet/GameplayStatics.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BehaviorTree != nullptr, TEXT("Behavior Tree is nullptr! Please assign BehaviorTree in your AIController")))
	{
		RunBehaviorTree(BehaviorTree);
	}

	// APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	// if (MyPawn != nullptr)
	// {
	// 	GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	// }
}
