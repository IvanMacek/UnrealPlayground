// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComponent, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPLAYGROUND_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ApplyHealthChange(AActor* Instigator, float Delta);

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool IsMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool IsAlive() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float HealthMax = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float Health = HealthMax;
};
