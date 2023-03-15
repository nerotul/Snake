// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "FloorBlock.h"


// Sets default values
AFloor::AFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();

	GenerateFloor(FloorSize, BlockSpawnLocation);
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloor::GenerateFloor(int Size, FVector& SpawnLocation)
{
	FVector Scale(0.5f);
	int SizeWithBorders = Size + 2;
	SpawnLocation.X -= BlockSize * (SizeWithBorders / 2);
	SpawnLocation.Y -= BlockSize * (SizeWithBorders / 2);
	SpawnLocation.Z -= 55;


	if (FloorElementClass != nullptr)
	{
		for (int i = 0; i < SizeWithBorders; i++)
		{
			for (int j = 0; j < SizeWithBorders; j++)
			{
				FTransform NewTransform(SpawnLocation);
				NewTransform.SetScale3D(Scale);

				AFloorBlock* NewFloorElement = GetWorld()->SpawnActor<AFloorBlock>(FloorElementClass, NewTransform);
				FloorBlocksLocations.Add(SpawnLocation);

				if (i == 0 || j == 0 || i == SizeWithBorders - 1 || j == SizeWithBorders - 1)
				{
					FVector ObstacleLocation = SpawnLocation;
					ObstacleLocation.Z += 50;
					FTransform ObstacleTransform(ObstacleLocation);
					ObstacleTransform.SetScale3D(Scale);

					AFloorBlock* NewObstacleElement = GetWorld()->SpawnActor<AFloorBlock>(FloorElementClass, ObstacleTransform);
				}

				SpawnLocation.X += BlockSize;

			}

			SpawnLocation.X -= (BlockSize * SizeWithBorders);
			SpawnLocation.Y += BlockSize;
		}
	}
}