// Fill out your copyright notice in the Description page of Project Settings.


#include "ODH/CSpear.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACSpear::ACSpear()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(L"Collision");
	SetRootComponent(CollisionComp);
	CollisionComp->SetBoxExtent(FVector(6.677329f, 77.277551f, 8.897527f));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(L"Mesh");
	MeshComp->SetupAttachment(CollisionComp);

// 	ConstructorHelpers::FObjectFinder<UStaticMesh> Temp_Spear(L"/Script/Engine.StaticMesh'/Game/ODH/Old_Wooden_Pole_ueqfdi0ga/Raw/ueqfdi0ga_tier_0.ueqfdi0ga_tier_0'");
// 	if (Temp_Spear.Succeeded())
// 	{
// 		MeshComp->SetStaticMesh(Temp_Spear.Object);
// 		MeshComp->SetRelativeLocation(FVector(3, -160, -7));
// 	}
}

