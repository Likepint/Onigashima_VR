// Fill out your copyright notice in the Description page of Project Settings.


#include "CPick.h"
#include "Components/BoxComponent.h"

// Sets default values
ACPick::ACPick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(L"Mesh");
	MeshComp->SetupAttachment(CollisionComp);

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(L"Collision");
	SetRootComponent(CollisionComp);

	

	ItemNum = 2;
}

