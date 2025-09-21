// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"

#include "DeathWall.h"
#include "EditorFontGlyphs.h"
#include "Space_Ship.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AAsteroid::AAsteroid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereBox = CreateDefaultSubobject<USphereComponent>("SphereBox");
	RootComponent = SphereBox;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->SetupAttachment(RootComponent);

	
	
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	RootComponent = Cast<UPrimitiveComponent>(GetRootComponent());
	RootComponent->SetSimulatePhysics(true);
	RootComponent->SetEnableGravity(false);
	RootComponent->AddForce(Seek());

	SphereBox->OnComponentBeginOverlap.AddDynamic(this, &AAsteroid::OnOverlapStart);
}

FVector AAsteroid::Seek()
{
	FVector vDesiredLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation()-GetActorLocation();
	vDesiredLocation.Normalize();
	vDesiredLocation *= FMath::RandRange(40000, 100000);
	return vDesiredLocation;
}

void AAsteroid::OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AProjectile* Projectile = Cast<AProjectile>(OtherActor);
	ASpace_Ship* SpaceShip = Cast<ASpace_Ship>(OtherActor);
	if (Projectile != nullptr)
	{
		hit();
		//if (hp==0)
		//{
		//	SpaceShip->score+=ScoreValue;
		//}
		Projectile->Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), hp));
	}
	
	if (SpaceShip!=nullptr)
	{
		if (SpaceShip->bHit==false)
		{
			SpaceShip->hit();
			hit();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), SpaceShip->hp));
		}
	}
	ADeathWall* Death = Cast<ADeathWall>(OtherActor);
	if (Death!=nullptr)
	{
		Destroy();
	}
	
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AAsteroid::hit()
{
	
	hp--;
	if (hp<=0)
	{
		Destroy();
		
	}
}

