// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Floor.generated.h"

class AFloorBlock;
class AFood;

UCLASS()
class SNAKEGAME_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AFloorBlock> FloorElementClass;

	UPROPERTY(EditAnywhere)
		int FloorSize; 
	UPROPERTY(EditAnywhere)
		float BlockSize = 60;


	void GenerateFloor(int InFloorSize, float InBlockSize, TSubclassOf<AFloorBlock> InFloorElementClass, FVector& InOutSpawnLocation, TArray<FVector>& OutFloorBlocksLocations);

	FVector BlockSpawnLocation;

	TArray<FVector> FloorBlocksLocations;


	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AFood> FoodClass;

	AFood* FoodPtr;

	UFUNCTION()
		void SpawnFood();
};
