// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SMagicProjectile.h"
#include "STeleportProjectile.generated.h"

UCLASS()
class UNREALPLAYGROUND_API ASTeleportProjectile : public ASMagicProjectile
{
	GENERATED_BODY()
	
public:	

	virtual void OnHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void StartTeleportAnim();

	void ProjectileExpired_TimerElapsed();
	void PortalEnter_TimerElapsed();

	FTimerHandle TimerHandle_ProjectileExpired;
	FTimerHandle TimerHandle_PortalEnter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* PortalEnterEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* PortalExitEffect;
};
