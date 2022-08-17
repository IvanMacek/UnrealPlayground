// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Media/Public/IMediaTracks.h"
#include "Particles/ParticleSystemComponent.h"

ASMagicProjectile::ASMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

    SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &ASMagicProjectile::OnHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnOverlap);

	RootComponent = SphereComp;
	
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.f;
	MovementComp->ProjectileGravityScale = 0.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(SphereComp);
}

void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	AudioComp->Activate();

	if (MuzzleFlashEffect != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlashEffect, GetActorLocation(), GetActorRotation());
	}
}

void ASMagicProjectile::OnHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	ApplyDamage(OtherActor);

	Explode();
	Destroy();

	const FString DebugText = FString::Printf(TEXT("Hit! (%.0f, %.0f, %.0f) %.0f"), HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, HitResult.ImpactPoint.Z, GetWorld()->TimeSeconds);
	DrawDebugString(GetWorld(), HitResult.ImpactPoint, DebugText, nullptr, FColor::Red, 1.f);
}

void ASMagicProjectile::OnOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ApplyDamage(OtherActor))
	{
		Explode();
		Destroy();
	}
}

void ASMagicProjectile::Explode() const
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorLocation(), GetActorRotation());

	if (HitSoundCue != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSoundCue, GetActorLocation());
	}

	UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShake, GetActorLocation(), 0.f, 1000.f);
}

bool ASMagicProjectile::ApplyDamage(const AActor* OtherActor)
{
	if (OtherActor != nullptr && OtherActor != GetInstigator())
	{
		USAttributeComponent* ActorAttributeComp = OtherActor->FindComponentByClass<USAttributeComponent>();
		if (ActorAttributeComp != nullptr)
		{
			ActorAttributeComp->ApplyHealthChange(GetInstigator(), -Damage);
			return true;
		}
	}

	return false;
}
