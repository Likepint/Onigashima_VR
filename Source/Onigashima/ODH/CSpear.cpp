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
	CollisionComp->SetRelativeScale3D(FVector(0.2f));
	CollisionComp->SetCollisionProfileName(L"Items");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACSpear::SpearOverlap);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(L"Mesh");
	MeshComp->SetupAttachment(CollisionComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh> Temp_Spear(L"/Script/Engine.StaticMesh'/Game/ODH/ItemAsset/Spear/Old_Wooden_Pole_ueqfdi0ga_Low.Old_Wooden_Pole_ueqfdi0ga_Low'");
	if (Temp_Spear.Succeeded())
	{
		MeshComp->SetStaticMesh(Temp_Spear.Object);
		MeshComp->SetRelativeLocation(FVector(3, -160, -7));
	}
	ItemNum=2;
}

void ACSpear::SetMesh(bool bValue)
{
	MeshComp->SetVisibility(bValue);
}

void ACSpear::SetCollision(bool bValue)
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

void ACSpear::SpearOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(3, 2.0f, FColor::Emerald, TEXT("Spear Overlap!"));
}

