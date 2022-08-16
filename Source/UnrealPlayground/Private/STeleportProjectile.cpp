// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASTeleportProjectile::ASTeleportProjectile()
{
}

void ASTeleportProjectile::OnHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	const FString DebugText = FString::Printf(TEXT("Hit! (%.0f, %.0f, %.0f) %.0f"), HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, HitResult.ImpactPoint.Z, GetWorld()->TimeSeconds);
	DrawDebugString(GetWorld(), HitResult.ImpactPoint, DebugText, nullptr, FColor::Blue, 1.f);

	StartTeleportAnim();
}

// Called when the game starts or when spawned
void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_ProjectileExpired, this, &ASTeleportProjectile::ProjectileExpired_TimerElapsed, 0.4f);
}

void ASTeleportProjectile::ProjectileExpired_TimerElapsed()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_ProjectileExpired);

	EffectComp->DeactivateSystem();
	MovementComp->StopMovementImmediately();
	Explode();

	StartTeleportAnim();
}

void ASTeleportProjectile::StartTeleportAnim()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PortalEnterEffect, GetInstigator()->GetActorLocation(), GetInstigator()->GetActorRotation());

	GetWorldTimerManager().SetTimer(TimerHandle_PortalEnter, this, &ASTeleportProjectile::PortalEnter_TimerElapsed, 0.2f);
}

void ASTeleportProjectile::PortalEnter_TimerElapsed()
{
	GetInstigator()->TeleportTo(GetActorLocation(), GetInstigator()->GetActorRotation());

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PortalExitEffect, GetInstigator()->GetActorLocation(), GetInstigator()->GetActorRotation());

	Destroy();
}

// Called every frame
void ASTeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
