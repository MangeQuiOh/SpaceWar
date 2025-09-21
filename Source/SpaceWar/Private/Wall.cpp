// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "Asteroid.h"
#include "Components/BoxComponent.h"


// Sets default values
AWall::AWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent=CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent=BoxComponent;
}

// Called when the game starts or when spawned
void AWall::BeginPlay() 
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AWall::SpawnAsteroid, FMath::RandRange(1,5), true);
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AWall::SpawnAsteroid()
{
	GetWorld()->SpawnActor<AAsteroid>(Asteroid,GetActorLocation()+FVector(FMath::RandRange(minX,maxX),FMath::RandRange(minY,maxY),0),GetActorRotation());
}

