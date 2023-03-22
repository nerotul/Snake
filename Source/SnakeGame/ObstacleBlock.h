// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "ObstacleBlock.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObstacleDestroyed);

UCLASS()
class SNAKEGAME_API AObstacleBlock : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactor, bool bIsHead) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float ObstacleExpirationTime = 5.0f;


	FOnObstacleDestroyed OnObstacleDestroyed;

	FTimerHandle TimerHandle_ObstacleLifeSpan;

	void DestroyExpiredObstacle();

};
