// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Media/Public/IMediaTracks.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionProfileName(TEXT("Projectile"));
	SphereComp->OnComponentHit.AddDynamic(this, &ASMagicProjectile::OnHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnOverlap);

	RootComponent = SphereComp;
	
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComp"));
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 1000.f;
	MovementComp->ProjectileGravityScale = 0.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ASMagicProjectile::OnHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	Explode();
	Destroy();

	const FString DebugText = FString::Printf(TEXT("Hit! (%.0f, %.0f, %.0f) %.0f"), HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, HitResult.ImpactPoint.Z, GetWorld()->TimeSeconds);
	DrawDebugString(GetWorld(), HitResult.ImpactPoint, DebugText, nullptr, FColor::Red, 1.f);
}

void ASMagicProjectile::OnOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		USAttributeComponent* ActorAttributeComp = OtherActor->FindComponentByClass<USAttributeComponent>();
		if (ActorAttributeComp != nullptr)
		{
			ActorAttributeComp->ApplyHealthChange(this, -Damage);

			Explode();
			Destroy();
		}
	}
}

void ASMagicProjectile::Explode() const
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorLocation(), GetActorRotation());
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
