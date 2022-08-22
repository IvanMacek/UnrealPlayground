// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Sound/SoundCue.h"
#include "SMagicProjectile.generated.h"

UCLASS()
class UNREALPLAYGROUND_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool ApplyDamage(AActor* OtherActor, const FHitResult& SweepResult);

	void Explode() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* EffectComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* HitEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* MuzzleFlashEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAudioComponent* AudioComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundCue* HitSoundCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Damage = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UCameraShakeBase> CameraShake;
};
