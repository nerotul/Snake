// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameGameStateBase.h"

ASnakeGameGameStateBase::ASnakeGameGameStateBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
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
