// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SCreditsComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, USCreditsComponent*, OwningComponent, int32, NewCredits, int32, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPLAYGROUND_API USCreditsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USCreditsComponent();

	UFUNCTION(BlueprintCallable, Category="Credits")
	static USCreditsComponent* GetCredits(const AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category="Credits")
	bool ApplyCreditsChange(int32 Delta);

	UPROPERTY(BlueprintAssignable, Category="Credits")
	FOnCreditsChanged OnCreditsChanged;

protected:

	UFUNCTION()
	void OnRep_Credits(int32 OldCredits);

	UPROPERTY(ReplicatedUsing="OnRep_Credits", EditDefaultsOnly, BlueprintReadOnly, Category="Credits")
	int32 Credits = 20;
};
