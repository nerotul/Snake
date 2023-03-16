// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "FloorBlock.h"
#include "Food.h"


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

	GenerateFloor(FloorSize, BlockSize, FloorElementClass, BlockSpawnLocation, FloorBlocksLocations);

}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloor::GenerateFloor(int InFloorSize, float InBlockSize, TSubclassOf<AFloorBlock> InFloorElementClass, FVector& InOutSpawnLocation, TArray<FVector>& OutFloorBlocksLocations)
{
	FVector Scale(0.5f);
	int SizeWithBorders = InFloorSize + 2;
	InOutSpawnLocation.X -= InBlockSize * (SizeWithBorders / 2);
	InOutSpawnLocation.Y -= InBlockSize * (SizeWithBorders / 2);
	InOutSpawnLocation.Z -= 55;


	if (IsValid(InFloorElementClass))
	{
		for (int i = 0; i < SizeWithBorders; i++)
		{
			for (int j = 0; j < SizeWithBorders; j++)
			{
				FTransform NewTransform(InOutSpawnLocation);
				NewTransform.SetScale3D(Scale);

				AFloorBlock* NewFloorElement = GetWorld()->SpawnActor<AFloorBlock>(InFloorElementClass, NewTransform);
				OutFloorBlocksLocations.Add(InOutSpawnLocation);

				if (i == 0 || j == 0 || i == SizeWithBorders - 1 || j == SizeWithBorders - 1)
				{
					FVector BorderLocation = InOutSpawnLocation;
					BorderLocation.Z += 50;
					FTransform BorderTransform(BorderLocation);
					BorderTransform.SetScale3D(Scale);

					AFloorBlock* NewBorderElement = GetWorld()->SpawnActor<AFloorBlock>(InFloorElementClass, BorderTransform);
				}

				InOutSpawnLocation.X += InBlockSize;

			}

			InOutSpawnLocation.X -= (InBlockSize * SizeWithBorders);
			InOutSpawnLocation.Y += InBlockSize;
		}
	}

	SpawnFood();
}

void AFloor::SpawnFood()
{
	if (IsValid(FoodClass))
	{
		int ArraySize = FloorBlocksLocations.Num();
		int RandArrayIndex = (rand() % (ArraySize - 1));
		FVector SpawnLocation = FloorBlocksLocations[RandArrayIndex];
		SpawnLocation.Z += 60;
		FTransform FoodTransform(SpawnLocation);

		FoodPtr = GetWorld()->SpawnActor<AFood>(FoodClass, FoodTransform);
		FoodPtr->OnDestroyed.AddDynamic(this, &AFloor::SpawnFood);
	}
}