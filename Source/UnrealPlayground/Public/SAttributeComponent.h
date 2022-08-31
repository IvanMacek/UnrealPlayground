// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComponent, float, NewHealth, float, Delta);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRageChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComponent, float, NewRage, float, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPLAYGROUND_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USAttributeComponent();

	UFUNCTION(BlueprintCallable, Category="Attributes")
	static USAttributeComponent* GetAttributes(const AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category="Attributes", meta=( DisplayName="IsAlive" ))
	static bool IsActorAlive(const AActor* Actor);

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool Kill(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ApplyRageChange(AActor* InstigatorActor, float Delta);

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool IsMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool IsLowHealth() const;

	UFUNCTION(BlueprintCallable, Category="Attributes")
	float GetHealthMax() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnRageChanged OnRageChanged;

protected:

	UFUNCTION(NetMulticast, Reliable)
	void MulticastHealthChanged(AActor* InstigatorActor, float NewHealth, float Delta);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRageChanged(AActor* InstigatorActor, float NewRage, float Delta);

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float HealthMax = 100.f;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float Health = HealthMax;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float RageMax = 100.f;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float Rage = 0.f;
};
