// Fill out your copyright notice in the Description page of Project Settings.


#include "ODH/CBow.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
ACBow::ACBow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(L"Mesh");
	SetRootComponent(MeshComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> Temp_Bow(L"/Script/Engine.StaticMesh'/Game/ODH/ItemAsset/Bow/cool_bow.cool_bow'");
	if (Temp_Bow.Succeeded())
	{
		MeshComp->SetStaticMesh(Temp_Bow.Object);
		//MeshComp->SetRelativeLocation(FVector(3, -160, -7));
		MeshComp->SetRelativeScale3D(FVector(0.1775f));

		CollisionComp = CreateDefaultSubobject<UBoxComponent>(L"Collision");
		CollisionComp->SetupAttachment(MeshComp);
		CollisionComp->SetRelativeLocation(FVector(0, -33.802818f, 2));
		CollisionComp->SetBoxExtent(FVector(60.520447f, 4.949969f, 5.551495f));
		CollisionComp->SetCollisionProfileName(L"BowString");

		FirePos = CreateDefaultSubobject<UArrowComponent>(L"FirePos");
		FirePos->SetupAttachment(MeshComp);
		FirePos->SetRelativeLocationAndRotation(FVector(0, 33.802818f, 11.267606f),FRotator(0,90,0));
	}

	ItemNum=1;
}

void ACBow::SetMesh(bool bValue)
{
	MeshComp->SetVisibility(bValue);
}

void ACBow::SetCollision(bool bValue)
{
	if (bValue)
	{
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

