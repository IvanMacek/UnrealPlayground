// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAttributeComponent.h"
#include "SInteractionComponent.h"
#include "SMagicProjectile.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "SCharacter.generated.h"

UCLASS()
class UNREALPLAYGROUND_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

	// Called every frame
	virtual void Tick(float const DeltaTime) override;

	void MoveForward(float const Value);
	void MoveRight(float const Value);
	void PrimaryAttack();
	void SecondaryAttack();
	void PrimaryInteract();
	void TeleportAction();

	void PrimaryAttack_TimerElapsed();
	void SecondaryAttack_TimerElapsed();
	void TeleportAction_TimerElapsed();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);

protected:

	void SpawnProjectile(TSubclassOf<AActor> ProjectileClass);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComponent, float NewHealth, float Delta);

	virtual FVector GetPawnViewLocation() const override;

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AttackAnimation;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> PrimaryProjectileClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> SecondaryProjectileClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> TeleportProjectileClass;

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_SecondaryAttack;
	FTimerHandle TimerHandle_TeleportAction;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USAttributeComponent* AttributeComp;

};
