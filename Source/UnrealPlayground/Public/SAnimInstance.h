// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SActionComponent.h"
#include "Animation/AnimInstance.h"
#include "SAnimInstance.generated.h"

UCLASS()
class UNREALPLAYGROUND_API USAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	bool bIsStunned;

	UPROPERTY(BlueprintReadOnly, Category="Animation")
	USActionComponent* ActionComp;
};
