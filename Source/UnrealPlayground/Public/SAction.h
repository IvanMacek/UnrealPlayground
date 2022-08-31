// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SAction.generated.h"

class USActionComponent;

USTRUCT()
struct FActionRepData
{
	GENERATED_BODY()

	UPROPERTY()
	bool bIsRunning;

	UPROPERTY()
	AActor* Instigator;
};

UCLASS(Blueprintable)
class UNREALPLAYGROUND_API USAction : public UObject
{
	GENERATED_BODY()

public:

	void Initialize(USActionComponent* NewActionComp);

	UFUNCTION(BlueprintNativeEvent, Category="Action")
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Action")
	void StopAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable, Category="Action")
	bool IsRunning() const;

	virtual bool IsSupportedForNetworking() const override;

	virtual UWorld* GetWorld() const override;

	UPROPERTY(EditDefaultsOnly, Category="Action")
	FName ActionName;

	UPROPERTY(EditDefaultsOnly, Category="Action")
	bool bAutoStart = false;

protected:

	UFUNCTION()
	void OnRep_RepData();

	UFUNCTION(BlueprintCallable, Category="Action")
	USActionComponent* GetOwningComponent() const;

	UPROPERTY(Replicated)
	USActionComponent* ActionComp;

	UPROPERTY(EditDefaultsOnly, Category="Tags")
	FGameplayTagContainer GrantsTags;

	UPROPERTY(EditDefaultsOnly, Category="Tags")
	FGameplayTagContainer BlockedTags;

	UPROPERTY(ReplicatedUsing="OnRep_RepData")
	FActionRepData RepData;
};
