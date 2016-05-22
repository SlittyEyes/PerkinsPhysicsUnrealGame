// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnBBalls.generated.h"

UCLASS()
class PERKINSPHYSICS_API ASpawnBBalls : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnBBalls();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//Returns WhereToSpawn
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	//Find Random Point in Wheretospawn box component
	UFUNCTION(BlueprintPure, Category = "Spawning")
		FVector GetRandomPointsInVolume();

protected:
	//What we are spawning
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> WhatToSpawn;

	//Timer for spawning
	FTimerHandle SpawnTimer;

	//Minimum Spawn Delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float SpawnDelayRangeLow;

	//Max Spawn Delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float SpawnDelayRangeHigh;

private:

	//Box Component indicating where to spawn pickups
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* WhereToSpawn;

	void SpawnPickup();

	//Current SpawnDelay
	float SpawnDelay;
};