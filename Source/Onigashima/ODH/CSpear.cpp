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

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(L"Mesh");
	MeshComp->SetupAttachment(CollisionComp);

	ItemNum = 1;
}

