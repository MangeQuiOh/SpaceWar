// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Projectile.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Space_Ship.generated.h"


UCLASS()
class SPACEWAR_API ASpace_Ship : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpace_Ship();

	bool bShoot = false;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	class UFloatingPawnMovement* FloatingMovement;

	UPROPERTY(EditAnywhere)
	float MoveScale;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float hp=3;

	bool bHit=false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	void Move(const struct FInputActionValue& ActionValue);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Shoot();

	void bShootModifier();

	void bHitModifier();

	void hit();
};
