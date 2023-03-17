// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "SnakeBase.h"
#include "Floor.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetFoodBonus(bIsAccelerating, bIsDoubleScore);
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFood::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			Snake->AddSnakeElement();

			if (bIsAccelerating == true)
			{
				Snake->MovementSpeed -= 0.02;
			}

			if (bIsDoubleScore == true)
			{
				
			}

			OnDestroyed.Broadcast();
			Destroy();
		}
	}
}

void AFood::SetFoodBonus(bool& InOutIsAccelerating, bool& InOutIsDoubleScore)
{
	float BonusChance = FMath::FRandRange(1, 100);

	if (BonusChance > 80)
	{
		float BonusType = FMath::FRandRange(1, 100);

		if (BonusType > 70)
		{
			InOutIsAccelerating = true;
		}
		else
		{
			InOutIsDoubleScore = true;
		}
	}
}
