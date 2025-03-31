// Fill out your copyright notice in the Description page of Project Settings.


#include "CPick.h"
#include "Components/BoxComponent.h"
#include "../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"

// Sets default values
ACPick::ACPick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(L"Collision");
	SetRootComponent(CollisionComp);
	CollisionComp->SetBoxExtent(FVector(17.485774f, 95.795314f, 21.668948f));
	CollisionComp->SetRelativeScale3D(FVector(0.1175f));
	CollisionComp->SetCollisionProfileName(L"Items");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACPick::PickOverlap);
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(L"Mesh");
	
	MeshComp->SetupAttachment(CollisionComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> Temp_Pick(L"/Script/Engine.StaticMesh'/Game/ODH/ItemAsset/Pick/pickaxe.pickaxe'");

	if (Temp_Pick.Succeeded())
	{
		MeshComp->SetStaticMesh(Temp_Pick.Object);
		MeshComp->SetRelativeLocation(FVector(0, -119.0, -6.0));
	}

	StoneEffect = CreateDefaultSubobject<UNiagaraComponent>(L"ChopEffect");
	StoneEffect->SetupAttachment(RootComponent);
	StoneEffect->SetAutoActivate(false);

	ItemNum=4;
}

void ACPick::SetMesh(bool bValue)
{
	MeshComp->SetVisibility(bValue);
}

void ACPick::SetCollision(bool bValue)
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

void ACPick::PickOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(3, 2.0f, FColor::Cyan, TEXT("Pick Overlap!"));

	StoneEffect->Activate(true);
}

