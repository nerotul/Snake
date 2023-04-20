// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeSaveGame.h"


ASnakeGameGameStateBase::ASnakeGameGameStateBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	LoadSaveGame();

}


void ASnakeGameGameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SnakeHungerTimer -= 1;
	OnHungerChange.Broadcast();

	if (SnakeHungerTimer <= 0)
	{
		OnStarved.Broadcast();
	}
}

void ASnakeGameGameStateBase::ResetHungerTimer()
{
	SnakeHungerTimer = SnakeMaxHungerTimer;
	OnHungerChange.Broadcast();
}

void ASnakeGameGameStateBase::LoadSaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		CurrentSaveGame = Cast<USnakeSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
		BestScore = CurrentSaveGame->BestScore;

	}
	else
	{
		CurrentSaveGame = Cast<USnakeSaveGame>(UGameplayStatics::CreateSaveGameObject(USnakeSaveGame::StaticClass()));
		UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SlotName, 0);
	}
}

void ASnakeGameGameStateBase::SaveSaveGame()
{
	if (IsValid(CurrentSaveGame))
	{
		if (Score > BestScore)
		{
			CurrentSaveGame = Cast<USnakeSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
			CurrentSaveGame->BestScore = Score;
			UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SlotName, 0);

		}
	}
}
