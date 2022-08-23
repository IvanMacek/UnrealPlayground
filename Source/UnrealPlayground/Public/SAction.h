// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.generated.h"

UCLASS(Blueprintable)
class UNREALPLAYGROUND_API USAction : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void StopAction(AActor* Instigator);

	virtual UWorld* GetWorld() const override;

	UPROPERTY(EditDefaultsOnly, Category="Action")
	FName ActionName;
};
