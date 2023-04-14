// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleBlock.h"
#include "SnakeBase.h"


// Sets default values
AObstacleBlock::AObstacleBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObstacleBlock::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_ObstacleLifeSpan, this, &AObstacleBlock::DestroyExpiredObstacle, 1, false, ObstacleExpirationTime);

}

// Called every frame
void AObstacleBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacleBlock::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			Snake->DestroySnake();
		}
	}
}

void AObstacleBlock::DestroyExpiredObstacle()
{
	OnObstacleDestroyed.Broadcast();
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ObstacleLifeSpan);
	Destroy();

}
