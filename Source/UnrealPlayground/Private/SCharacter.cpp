// Fill out your copyright notice in the Description page of Project Settings.

#include "SCharacter.h"
#include "DrawDebugHelpers.h"
#include "SMagicProjectile.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>(TEXT("InteractionComp"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	// -- Rotation Visualization -- //
	constexpr float DrawScale = 100.0f;
	constexpr float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	const FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	const FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
}

void ASCharacter::MoveForward(const float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0;
	ControlRot.Roll = 0;
	
	AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float const Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0;
	ControlRot.Roll = 0;

	AddMovementInput(UKismetMathLibrary::GetRightVector(ControlRot), Value);
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnimation);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimerElapsed, 0.2f);
}

void ASCharacter::SecondaryAttack()
{
	PlayAnimMontage(AttackAnimation);

	GetWorldTimerManager().SetTimer(TimerHandle_SecondaryAttack, this, &ASCharacter::SecondaryAttack_TimerElapsed, 0.2f);
}

void ASCharacter::TeleportAction()
{
	PlayAnimMontage(AttackAnimation);

	GetWorldTimerManager().SetTimer(TimerHandle_TeleportAction, this, &ASCharacter::TeleportAction_TimerElapsed, 0.2f);
}

void ASCharacter::PrimaryAttack_TimerElapsed()
{
	FMinimalViewInfo CameraView;
	CameraComp->GetCameraView(0, CameraView);

	FVector& AimStart = CameraView.Location;
	FVector AimEnd = CameraView.Location + CameraView.Rotation.Vector() * 10000.f;

	float DebugLifeTime = 1.f;
	FColor DebugColor = FColor::Magenta;
	DrawDebugLine(GetWorld(), AimStart, AimEnd, DebugColor, false, DebugLifeTime);

	FHitResult AimHit;
	bool bHit = GetWorld()->LineTraceSingleByChannel(AimHit, AimStart, AimEnd, ECC_WorldDynamic);
	if (bHit)
	{
		DrawDebugSphere(GetWorld(), AimHit.ImpactPoint, 6.f, 6, DebugColor, false, DebugLifeTime);
	}

	const FVector MuzzleLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FRotator SpawnVector = UKismetMathLibrary::FindLookAtRotation(MuzzleLocation, bHit ? AimHit.ImpactPoint : AimEnd);
	const FTransform SpawnTrans = FTransform(SpawnVector, MuzzleLocation);

	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;

	GetWorld()->SpawnActor<AActor>(PrimaryProjectileClass, SpawnTrans, SpawnParameters);
}

void ASCharacter::SecondaryAttack_TimerElapsed()
{
	FMinimalViewInfo CameraView;
	CameraComp->GetCameraView(0, CameraView);

	FVector& AimStart = CameraView.Location;
	FVector AimEnd = CameraView.Location + CameraView.Rotation.Vector() * 10000.f;

	float DebugLifeTime = 1.f;
	FColor DebugColor = FColor::Magenta;
	DrawDebugLine(GetWorld(), AimStart, AimEnd, DebugColor, false, DebugLifeTime);

	FHitResult AimHit;
	bool bHit = GetWorld()->LineTraceSingleByChannel(AimHit, AimStart, AimEnd, ECC_WorldDynamic);
	if (bHit)
	{
		DrawDebugSphere(GetWorld(), AimHit.ImpactPoint, 6.f, 6, DebugColor, false, DebugLifeTime);
	}

	const FVector MuzzleLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FRotator SpawnVector = UKismetMathLibrary::FindLookAtRotation(MuzzleLocation, bHit ? AimHit.ImpactPoint : AimEnd);
	const FTransform SpawnTrans = FTransform(SpawnVector, MuzzleLocation);

	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;

	GetWorld()->SpawnActor<AActor>(SecondaryProjectileClass, SpawnTrans, SpawnParameters);
}

void ASCharacter::TeleportAction_TimerElapsed()
{
	FMinimalViewInfo CameraView;
	CameraComp->GetCameraView(0, CameraView);

	FVector& AimStart = CameraView.Location;
	FVector AimEnd = CameraView.Location + CameraView.Rotation.Vector() * 10000.f;

	float DebugLifeTime = 1.f;
	FColor DebugColor = FColor::Magenta;
	DrawDebugLine(GetWorld(), AimStart, AimEnd, DebugColor, false, DebugLifeTime);

	FHitResult AimHit;
	bool bHit = GetWorld()->LineTraceSingleByChannel(AimHit, AimStart, AimEnd, ECC_WorldDynamic);
	if (bHit)
	{
		DrawDebugSphere(GetWorld(), AimHit.ImpactPoint, 6.f, 6, DebugColor, false, DebugLifeTime);
	}

	const FVector MuzzleLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FRotator SpawnVector = UKismetMathLibrary::FindLookAtRotation(MuzzleLocation, bHit ? AimHit.ImpactPoint : AimEnd);
	const FTransform SpawnTrans = FTransform(SpawnVector, MuzzleLocation);

	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;

	GetWorld()->SpawnActor<AActor>(TeleportProjectileClass, SpawnTrans, SpawnParameters);
}

void ASCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction(TEXT("PrimaryAttack"), EInputEvent::IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction(TEXT("SecondaryAttack"), EInputEvent::IE_Pressed, this, &ASCharacter::SecondaryAttack);
	PlayerInputComponent->BindAction(TEXT("PrimaryInteract"), EInputEvent::IE_Pressed, this, &ASCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction(TEXT("TeleportAction"), EInputEvent::IE_Pressed, this, &ASCharacter::TeleportAction);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
}
