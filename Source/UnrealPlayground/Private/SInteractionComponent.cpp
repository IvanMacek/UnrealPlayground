// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "CollisionDebugDrawingPublic.h"
#include "DrawDebugHelpers.h"
#include "SGameplayInterface.h"


static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("su.DebugDrawInteraction"), true, TEXT("Enable Debug Lines dor Interact Component."), ECVF_Cheat);


USInteractionComponent::USInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USInteractionComponent::PrimaryInteract()
{
	const bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	FVector EyeLocation;
	FRotator EyeRotation;
	GetOwner()->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	const FVector Start = EyeLocation;
	const FVector End = EyeLocation + EyeRotation.Vector() * 1000;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(30.f);

	TArray<FHitResult> HitResults;
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(HitResults, Start, End, FQuat::Identity, ObjectQueryParams, CollisionShape);

	FColor HitColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (auto HitResult : HitResults)
	{
		if (bDebugDraw)
		{
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, CollisionShape.GetSphereRadius(), 32, HitColor, false, 2.f);
		}

		AActor* HitActor = HitResult.GetActor();
		if (HitActor != nullptr)
		{
			if (HitActor->Implements<USGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(GetOwner());
				ISGameplayInterface::Execute_Interact(HitActor, MyPawn);
			}

			break;
		}
	}

	if (bDebugDraw)
	{
		DrawDebugLine(GetWorld(), Start, End, HitColor, false, 2.f);
	}
}
