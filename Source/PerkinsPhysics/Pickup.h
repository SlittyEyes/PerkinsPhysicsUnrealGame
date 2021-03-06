// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class PERKINSPHYSICS_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Return Mesh of Pickup
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; }

private:
	// Static Mesh to represent the pickups
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "PickUp", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* PickupMesh;
	
	
};
