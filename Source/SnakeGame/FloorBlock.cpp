// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorBlock.h"
#include "SnakeBase.h"

// Sets default values
AFloorBlock::AFloorBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void AFloorBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloorBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorBlock::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			Snake->Destroy();
		}
	}
}
