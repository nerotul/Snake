// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "SnakeBase.h"
#include "Floor.h"
#include "SnakeGameGameStateBase.h"

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

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_FoodLifeSpan, this, &AFood::DestroyExpiredFood, 1, false, FoodExpirationTime);
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFood::Interact(AActor* Interactor, bool bIsHead)
{
	ASnakeGameGameStateBase* GameStatePtr = GetWorld()->GetGameState<ASnakeGameGameStateBase>();

	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake) && IsValid(GameStatePtr))
		{
			Snake->AddSnakeElement();
			GameStatePtr->Score += 100;
			GameStatePtr->OnScoreChange.Broadcast();
			GameStatePtr->ResetHungerTimer();

			if (bIsAccelerating == true)
			{
				Snake->MovementSpeed -= 0.02;
			}

			if (bIsDoubleScore == true)
			{
				GameStatePtr->Score += 100;
				GameStatePtr->OnScoreChange.Broadcast();

			}

			OnFoodDestroyed.Broadcast();
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_FoodLifeSpan);
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

void AFood::DestroyExpiredFood()
{
	OnFoodDestroyed.Broadcast();
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_FoodLifeSpan);
	Destroy();
}
