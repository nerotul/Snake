// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SnakeGameGameStateBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScoreChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSnakeDead);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHungerChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStarved);


UCLASS()
class SNAKEGAME_API ASnakeGameGameStateBase : public AGameStateBase
{
	GENERATED_BODY()


public:

	ASnakeGameGameStateBase();

	virtual void Tick(float DeltaTime) override;

	FOnHungerChange OnHungerChange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float SnakeMaxHungerTimer = 1000;

	float SnakeHungerTimer = SnakeMaxHungerTimer;

	void ResetHungerTimer();

	FOnStarved OnStarved;

	UPROPERTY(BlueprintReadOnly)
		int Score = 0;

	FOnScoreChange OnScoreChange;
	FOnSnakeDead OnSnakeDead;

};
