// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UCLASS()
class SPACEWAR_API AAsteroid : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAsteroid();

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPrimitiveComponent* RootComponent;
	
	float hp=FMath::RandRange(1,3);
	float ScoreValue = hp;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector Seek();
	UFUNCTION() void OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void hit();
};
