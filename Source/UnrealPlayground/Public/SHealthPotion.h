// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SHealthPotion.generated.h"

UCLASS()
class UNREALPLAYGROUND_API ASHealthPotion : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	ASHealthPotion();

	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	virtual void BeginPlay() override;

	void Show();
	void Hide();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float HealingAmount = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RefillTimeout = 5.f;
};
