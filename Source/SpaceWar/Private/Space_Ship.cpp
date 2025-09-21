// Fill out your copyright notice in the Description page of Project Settings.


#include "Space_Ship.h"
#include "SpaceController.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PlayerController.h"
#include "Projectile.h"



// Sets default values
ASpace_Ship::ASpace_Ship()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereBox = CreateDefaultSubobject<USphereComponent>("SphereBox");
	RootComponent = SphereBox;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->SetupAttachment(RootComponent);

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	MoveScale = 1.f;
	
}

// Called when the game starts or when spawned
void ASpace_Ship::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpace_Ship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void ASpace_Ship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	ASpaceController* AC = Cast<ASpaceController>(Controller);
	check(EIC && AC);
	EIC->BindAction(AC->MoveAction, ETriggerEvent::Triggered, this, &ASpace_Ship::Move);
	EIC->BindAction(AC->ShootAction, ETriggerEvent::Triggered, this, &ASpace_Ship::Shoot);

	ULocalPlayer* LocalPlayer=AC->GetLocalPlayer();
	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(AC->PawnMappingInput, 0);
}

void ASpace_Ship::Move(const FInputActionValue& ActionValue)
{
	FVector Input = ActionValue.Get<FInputActionValue::Axis3D>();
	AddMovementInput(GetActorRotation().RotateVector(Input),MoveScale);
	
}

void ASpace_Ship::Shoot()
{
	if (bShoot == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("This is a log message!"));
		GetWorld()->SpawnActor<AProjectile>(projectile, GetActorLocation(), GetActorRotation());
		bShoot=true;
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpace_Ship::bShootModifier, 0.35, false);
	}
}

void ASpace_Ship::bShootModifier()
{
	bShoot=false;
}

void ASpace_Ship::bHitModifier()
{
	bHit=false;
}

void ASpace_Ship::hit()
{
	if (bHit==false)
	{
		hp--;
		bHit=true;
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpace_Ship::bHitModifier, 1.0f, false);
		if (hp == 0)
		{
			Destroy();
		}
	}
	
}



