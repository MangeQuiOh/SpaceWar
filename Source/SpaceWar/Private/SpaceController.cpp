// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceController.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"

void ASpaceController::MapKey(UInputMappingContext* InputMappingContext, UInputAction* InputAction, FKey Key, bool bNegate, bool bSwizzle, EInputAxisSwizzle SwizzleOrder)
{
	FEnhancedActionKeyMapping& Mapping = InputMappingContext->MapKey(InputAction, Key);
	UObject* outer = InputMappingContext->GetOuter();

	if (bNegate)
	{
		UInputModifierNegate* Negate = NewObject<UInputModifierNegate>(outer);
		Mapping.Modifiers.Add(Negate);
	}

	if (bSwizzle)
	{
		UInputModifierSwizzleAxis* Swizzle = NewObject<UInputModifierSwizzleAxis>(outer);
		Swizzle-> Order = SwizzleOrder;
		Mapping.Modifiers.Add(Swizzle);
	}
}

void ASpaceController::SetupInputComponent()
{
	Super::SetupInputComponent();

	PawnMappingInput = NewObject<UInputMappingContext>(this);

	MoveAction = NewObject<UInputAction>(this);
	ShootAction = NewObject<UInputAction>(this);
	MoveAction->ValueType = EInputActionValueType::Axis3D;
	MapKey(PawnMappingInput, MoveAction, EKeys::W);
	MapKey(PawnMappingInput, MoveAction, EKeys::S, true);
	MapKey(PawnMappingInput, MoveAction, EKeys::A,true,true);
	MapKey(PawnMappingInput, MoveAction, EKeys::D,false,true);
	MapKey(PawnMappingInput, ShootAction, EKeys::SpaceBar);
}

