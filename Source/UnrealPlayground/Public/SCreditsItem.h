// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SCreditsItem.generated.h"

UCLASS()
class UNREALPLAYGROUND_API ASCreditsItem : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

public:
	ASCreditsItem();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	virtual FText GetInteractText_Implementation(APawn* InstigatorPawn) override;

	UFUNCTION(BlueprintNativeEvent)
	void OnCreditsChangeApplied(APawn* InstigatorPawn);

protected:

	UFUNCTION()
	void OnRep_Visible();

	void Show();
	void Hide();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RespawnTimeout = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 CreditsChange = 30;

	UPROPERTY(ReplicatedUsing="OnRep_Visible")
	bool bVisible = true;
};
