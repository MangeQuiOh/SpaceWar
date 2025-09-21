// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeathWall.generated.h"

UCLASS()
class SPACEWAR_API ADeathWall : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponent;

public:
	// Sets default values for this actor's properties
	ADeathWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
