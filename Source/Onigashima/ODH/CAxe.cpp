﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ODH/CAxe.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Global.h"
#include "../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
#include "GameFramework/Character.h"
#include "PJS/Components/CInventoryComponent.h"
#include "PJS/Crafts/CItem_Stone.h"
#include "PJS/Crafts/CItem_Planks.h"


// Sets default values
ACAxe::ACAxe()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(L"Collision");
	SetRootComponent(CollisionComp);
	CollisionComp->SetBoxExtent(FVector(6.729334f, 7.245102f, 3.92625f));
	CollisionComp->SetCollisionProfileName(L"Items");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this,&ACAxe::AxeOverlap);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(L"Mesh");
	MeshComp->SetupAttachment(CollisionComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> Temp_Axe(L"/Script/Engine.StaticMesh'/Game/ODH/ItemAsset/Axe/Medium/ueqgcaifa_tier_2.ueqgcaifa_tier_2'");

	if (Temp_Axe.Succeeded())
	{
		MeshComp->SetStaticMesh(Temp_Axe.Object);
		MeshComp->SetRelativeLocation(FVector(-18,-4,-2));
	}

	ChopEffect = CreateDefaultSubobject<UNiagaraComponent>(L"ChopEffect");
	ChopEffect->SetupAttachment(RootComponent);
	ChopEffect->SetAutoActivate(false);

	ItemNum=3;
}

void ACAxe::SetMesh(bool bValue)
{
	MeshComp->SetVisibility(bValue);
}

void ACAxe::SetCollision(bool bValue)
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

void ACAxe::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void ACAxe::AxeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(3, 2.0f, FColor::Blue, TEXT("Axe Overlap!"));

	UGameplayStatics::PlaySoundAtLocation(this,AxeSound,GetActorLocation());

	ChopEffect->Activate(true);

	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CheckNull(inventory);

	if (ACItem_Stone* stone = Cast<ACItem_Stone>(OtherActor))
	{
		inventory->GetInventory().Add(stone->GetClass(), FMath::RandRange(1, 10));

		return;
	}

	if (ACItem_Planks* planks = Cast<ACItem_Planks>(OtherActor))
	{
		inventory->GetInventory().Add(planks->GetClass(), FMath::RandRange(1, 10));

		return;
	}

}

