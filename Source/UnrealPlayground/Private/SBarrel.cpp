// Fill out your copyright notice in the Description page of Project Settings.


#include "SBarrel.h"

#include "SMagicProjectile.h"
#include "Builders/CylinderBuilder.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASBarrel::ASBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComp->SetCollisionProfileName("Barrel");
	StaticMeshComp->SetSimulatePhysics(true);
		
	RootComponent = StaticMeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForceComp->SetupAttachment(StaticMeshComp);
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->ImpulseStrength = 1000.f;
	RadialForceComp->Radius = 2000.f;
	RadialForceComp->DestructibleDamage = 500.f;
}

// Called when the game starts or when spawned
void ASBarrel::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMeshComp->OnComponentHit.AddDynamic(this, &ASBarrel::OnHit);
}

// Called every frame
void ASBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	if (OtherActor->IsA<ASMagicProjectile>())
 	{
 		RadialForceComp->FireImpulse();
 	}
}

