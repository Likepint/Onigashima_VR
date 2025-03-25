

// Fill out your copyright notice in the Description page of Project Settings.


#include "ODH/CArrow.h"
#include "Components/BoxComponent.h"
#include "Global.h"

// Sets default values
ACArrow::ACArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(L"Collision");
	SetRootComponent(Collision);

	ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(L"ArrowMesh");
	ArrowMesh->SetupAttachment(Collision);

	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(L"/Script/Engine.StaticMesh'/Game/ODH/Old_Wooden_Pole_ueqfdi0ga/Old_Wooden_Pole_ueqfdi0ga_Low.Old_Wooden_Pole_ueqfdi0ga_Low'");
	if (TempMesh.Succeeded())
	{
		ArrowMesh->SetStaticMesh(TempMesh.Object);
	}

	/*CHelpers::GetAsset(&ArrowMesh, "/Script/Engine.StaticMesh'/Game/ODH/Old_Wooden_Pole_ueqfdi0ga/Old_Wooden_Pole_ueqfdi0ga_Low.Old_Wooden_Pole_ueqfdi0ga_Low'");*/
	
}

// Called when the game starts or when spawned
void ACArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACArrow::SetActive(bool bValue)
{
	ArrowMesh->SetVisibility(bValue);

	if (bValue)
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

