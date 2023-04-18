// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FloorBlock.h"
#include "Food.h"
#include "ObstacleBlock.h"
#include "SnakeElementBase.h"


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
	GetWorld()->GetTimerManager().SetTimer(InitalDelay, this, &AFloor::InitialFoodObstacleSpawn, 1, false, 0.2);

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

		TArray<AActor*> Actors;
		FHitResult Hit;
		FVector EndTraceLocation = FVector(SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z * 100);

		UKismetSystemLibrary::LineTraceSingle(GetWorld(), SpawnLocation, EndTraceLocation,
			ETraceTypeQuery::TraceTypeQuery4, false, Actors, EDrawDebugTrace::ForDuration,
			Hit, true, FLinearColor::Green, FLinearColor::Red, 5.0f);

		if (Hit.Actor == nullptr)
		{
			FoodPtr = GetWorld()->SpawnActor<AFood>(FoodClass, FoodTransform);
			FoodPtr->OnFoodDestroyed.AddDynamic(this, &AFloor::SpawnFood);
		}
		else
		{
			SpawnFood();
		}
	}
}

void AFloor::SpawnObstacle()
{
	if (IsValid(ObstacleClass))
	{
		int ArraySize = FloorBlocksLocations.Num();
		int RandArrayIndex = (rand() % (ArraySize - 1));
		FVector SpawnLocation = FloorBlocksLocations[RandArrayIndex];
		SpawnLocation.Z += 60;
		FTransform ObstacleBlockTransform(SpawnLocation);

		TArray<AActor*> Actors;
		FHitResult Hit;
		FVector EndTraceLocation = FVector(SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z * 100);

		UKismetSystemLibrary::LineTraceSingle(GetWorld(), SpawnLocation, EndTraceLocation,
			ETraceTypeQuery::TraceTypeQuery4, false, Actors, EDrawDebugTrace::ForDuration,
			Hit, true, FLinearColor::Blue, FLinearColor::Yellow, 5.0f);

		if (Hit.Actor == nullptr)
		{
			ObstacleBlockPtr = GetWorld()->SpawnActor<AObstacleBlock>(ObstacleClass, ObstacleBlockTransform);
			FVector PreviousBlockLocation = ObstacleBlockPtr->GetActorLocation();
			ObstacleBlockPtr->OnObstacleDestroyed.AddDynamic(this, &AFloor::SpawnObstacle);

			int32 AdditionalBlocksCount = FMath::RandRange(MinObstacleElementsCount, MaxObstacleElementsCount);

			for (int i = 0; i < AdditionalBlocksCount - 1; i++)
			{
				FVector AdditionalBlockLocation = PreviousBlockLocation;
				
				// Fully random spawn
				//int32 XSign = FMath::RandRange(-1, 1);
				//AdditionalBlockLocation.X += (BlockSize * XSign);

				//int32 YSign = FMath::RandRange(-1, 1);
				//AdditionalBlockLocation.Y += (BlockSize * YSign);

				// Orthogonal spawn
				bool IsX = FMath::RandBool();
				bool IsPositive = FMath::RandBool();
				if (IsX == true)
				{
					if (IsPositive == true)
					{
						AdditionalBlockLocation.X += BlockSize;
					}
					else
					{
						AdditionalBlockLocation.X -= BlockSize;
					}
				}
				else
				{
					if (IsPositive == true)
					{
						AdditionalBlockLocation.Y += BlockSize;
					}
					else
					{
						AdditionalBlockLocation.Y -= BlockSize;
					}
				}


				FHitResult AdditionalHit;
				FVector EndAdditionalTraceLocation = FVector(AdditionalBlockLocation.X, AdditionalBlockLocation.Y, AdditionalBlockLocation.Z * 100);
				FTransform AdditionalObstacleTransform(AdditionalBlockLocation);

				UKismetSystemLibrary::LineTraceSingle(GetWorld(), AdditionalBlockLocation, EndAdditionalTraceLocation,
					ETraceTypeQuery::TraceTypeQuery4, false, Actors, EDrawDebugTrace::ForDuration,
					AdditionalHit, true, FLinearColor::Blue, FLinearColor::Yellow, 5.0f);

				const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
				UClass* ActorsFilter = ASnakeElementBase::StaticClass();
				TArray<AActor*> IgnoredActors;
				TArray<AActor*> OutActors;

				UKismetSystemLibrary::SphereOverlapActors(GetWorld(), AdditionalBlockLocation, 120, ObjectTypes, ActorsFilter, IgnoredActors, OutActors);

				if (AdditionalHit.Actor == nullptr && OutActors.Num() == 0)
				{
					AObstacleBlock* AdditionalObstacleBlockPtr = GetWorld()->SpawnActor<AObstacleBlock>(ObstacleClass, AdditionalObstacleTransform);
					PreviousBlockLocation = AdditionalObstacleBlockPtr->GetActorLocation();
				}
			}
		}
		else
		{
			SpawnObstacle();
		}
	}
}

void AFloor::InitialFoodObstacleSpawn()
{
	SpawnFood();

	for (int i = 0; i < ObstacleGroupsPerSpawn; i++)
	{
		SpawnObstacle();
	}

}
