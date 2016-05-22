// Fill out your copyright notice in the Description page of Project Settings.

#include "PerkinsPhysics.h"
#include "SpawnBBalls.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pickup.h"



// Sets default values
ASpawnBBalls::ASpawnBBalls()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;

	//Set SpawnDelay Range
	SpawnDelayRangeLow = 1.0f;
	SpawnDelayRangeHigh = 4.5f;

}

// Called when the game starts or when spawned
void ASpawnBBalls::BeginPlay()
{
	Super::BeginPlay();

	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnBBalls::SpawnPickup, SpawnDelay, false);
}

// Called every frame
void ASpawnBBalls::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

FVector ASpawnBBalls::GetRandomPointsInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void ASpawnBBalls::SpawnPickup()
{
	if (WhatToSpawn != NULL) 
	{	
		//Checking if there is a game world
		UWorld* const World = GetWorld();
		if(World)
		{
			
			//Spawn Parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			//Get Spawning Location
			FVector SpawnLocation = GetRandomPointsInVolume();

			//Get random rotation of spawned item
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;
			
			//spawn this pickup
			APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

			SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnBBalls::SpawnPickup, SpawnDelay, false);
		}
	
	}

}