// Fill out your copyright notice in the Description page of Project Settings.


#include "ODH/CAxe.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Global.h"


// Sets default values
ACAxe::ACAxe()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(L"Collision");
	SetRootComponent(CollisionComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(L"Mesh");
	MeshComp->SetupAttachment(CollisionComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> Temp_Axe(L"/Script/Engine.StaticMesh'/Game/ODH/Axe_ueqgcaifa/Medium/ueqgcaifa_tier_2.ueqgcaifa_tier_2'");

	if (Temp_Axe.Succeeded())
	{
		MeshComp->SetStaticMesh(Temp_Axe.Object);
	}

	ItemNum = 3;
}


