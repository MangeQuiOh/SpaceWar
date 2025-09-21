// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "SpaceController.generated.h"

/**
 * 
 */
UCLASS()
class SPACEWAR_API ASpaceController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;
	
	UPROPERTY()
	class UInputMappingContext* PawnMappingInput;

	UPROPERTY()
	class UInputAction* MoveAction;

	UPROPERTY()
	class UInputAction* ShootAction;

	

	void MapKey(UInputMappingContext* InputMappingContext, UInputAction* InputAction, FKey Key,
	bool bNegate=false, bool bSwizzle = false, EInputAxisSwizzle SwizzleOrder = EInputAxisSwizzle::YXZ);
};


