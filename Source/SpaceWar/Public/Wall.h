// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Asteroid.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

UCLASS()
class SPACEWAR_API AWall : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	float minX;

	UPROPERTY(EditAnywhere)
	float maxX;

	UPROPERTY(EditAnywhere)
	float minY;

	UPROPERTY(EditAnywhere)
	float maxY;

public:
	// Sets default values for this actor's properties
	AWall();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAsteroid> Asteroid;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnAsteroid();
};

