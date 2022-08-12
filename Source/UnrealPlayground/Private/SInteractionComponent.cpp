// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "CollisionDebugDrawingPublic.h"
#include "DrawDebugHelpers.h"
#include "SGameplayInterface.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
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
	//GetWorld()->LineTraceSingleByObjectType(HitResult[0], Start, End, ObjectQueryParams);
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(HitResults, Start, End, FQuat::Identity, ObjectQueryParams, CollisionShape);

	FColor HitColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (auto HitResult : HitResults)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, CollisionShape.GetSphereRadius(), 32, HitColor, false, 2.f);

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

	DrawDebugLine(GetWorld(), Start, End, HitColor, false, 2.f);
	//DrawLineTraces(GetWorld(), Start, End, HitResults, 2.);
	//DrawSphereSweeps(GetWorld(), Start, End, CollisionShape.GetSphereRadius(), HitResults, 2.f);
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
