// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Food.generated.h"

class AFloor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFoodDestroyed);

UCLASS()
class SNAKEGAME_API AFood : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFood();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactor, bool bIsHead) override;

	void SetFoodBonus(bool& InOutIsAccelerating, bool& InOutIsDoubleScore);

	void DestroyExpiredFood();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool bIsAccelerating;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool bIsDoubleScore;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float FoodExpirationTime = 10.0f;

	FOnFoodDestroyed OnFoodDestroyed;

	FTimerHandle TimerHandle_FoodLifeSpan;
};
