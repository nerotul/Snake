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


class USnakeSaveGame;

UCLASS()
class SNAKEGAME_API ASnakeGameGameStateBase : public AGameStateBase
{
	GENERATED_BODY()


public:

	ASnakeGameGameStateBase();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
		FOnHungerChange OnHungerChange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float SnakeMaxHungerTimer = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float SnakeHungerTimer = SnakeMaxHungerTimer;

	void ResetHungerTimer();

	UPROPERTY(BlueprintAssignable)
		FOnStarved OnStarved;

	UPROPERTY(BlueprintReadOnly)
		int Score = 0;

	UPROPERTY(BlueprintAssignable)
		FOnScoreChange OnScoreChange;
	UPROPERTY(BlueprintAssignable)
		FOnSnakeDead OnSnakeDead;

	USnakeSaveGame* CurrentSaveGame;
	UPROPERTY()
		FString SlotName = "SnakeSave";
	UPROPERTY(BlueprintReadOnly)
		int BestScore;

	void LoadSaveGame();

	void SaveSaveGame();

};
