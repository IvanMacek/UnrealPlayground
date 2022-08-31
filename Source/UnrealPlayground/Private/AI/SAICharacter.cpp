// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "SWorldUserWidget.h"
#include "AI/SBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	ActionComp = CreateDefaultSubobject<USActionComponent>("ActionComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
}

void ASAICharacter::SetTargetActor(AActor* NewTarget)
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		UBlackboardComponent* BBComp = AIController->GetBlackboardComponent();
		BBComp->SetValueAsObject("TargetActor", NewTarget);
	}
}

AActor* ASAICharacter::GetTargetActor()
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		const UBlackboardComponent* BBComp = AIController->GetBlackboardComponent();
		return Cast<AActor>(BBComp->GetValueAsObject("TargetActor"));
	}

	return nullptr;
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);
	AttributeComp->OnHealthChanged.AddDynamic(this, &ASAICharacter::OnHealthChanged);
}

void ASAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComponent, float NewHealth, float Delta)
{
	if (Delta < 0.f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("HitFlashTime", GetWorld()->GetTimeSeconds());

		if (InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}

		if (ActiveHealthBar == nullptr)
		{
			ActiveHealthBar = CreateWidget<USWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
			if (ActiveHealthBar != nullptr)
			{
				ActiveHealthBar->AttachedActor = this;
				ActiveHealthBar->AddToViewport();
			}
		}

		if (!AttributeComp->IsAlive())
		{
			const AAIController* AIController = Cast<AAIController>(GetController());
			if (AIController != nullptr)
			{
				AIController->GetBrainComponent()->StopLogic("Killed");
			}

			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();

			SetLifeSpan(10.f);
		}
	}
}

void ASAICharacter::OnPawnSeen_Implementation(APawn* Pawn)
{
	if (GetTargetActor() != Pawn)
	{
		SetTargetActor(Pawn);

		MulticastPawnSeen();
	}
}

void ASAICharacter::MulticastPawnSeen_Implementation()
{
	if (USWorldUserWidget* NewWidget = CreateWidget<USWorldUserWidget>(GetWorld(), SpottedWidgetClass))
	{
		NewWidget->AttachedActor = this;
		NewWidget->AddToViewport(10);
	}
}
