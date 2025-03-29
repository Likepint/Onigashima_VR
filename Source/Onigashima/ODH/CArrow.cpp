

// Fill out your copyright notice in the Description page of Project Settings.


#include "ODH/CArrow.h"
#include "Components/BoxComponent.h"
#include "Global.h"
#include "../KJY/CEnemy.h"

// Sets default values
ACArrow::ACArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(L"Collision");
	Collision->SetCollisionProfileName(L"Items");
	SetRootComponent(Collision);
	Collision->SetBoxExtent(FVector(38.451927f, 0.832166f, 1.710501f));
	Collision->OnComponentBeginOverlap.AddDynamic(this,&ACArrow::ArrowOverlap);

	ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(L"ArrowMesh");
	ArrowMesh->SetupAttachment(Collision);

	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(L"/Script/Engine.StaticMesh'/Game/ODH/ItemAsset/Arrow/cc0_wooden_arrow.cc0_wooden_arrow'");
	if (TempMesh.Succeeded())
	{
		ArrowMesh->SetStaticMesh(TempMesh.Object);
		ArrowMesh->SetRelativeRotation(FRotator(45, -30, 0));
	}
}

// Called when the game starts or when spawned
void ACArrow::BeginPlay()
{
	Super::BeginPlay();
	
	/*Velocity = GetActorForwardVector() * 2000;*/
}

// Called every frame
void ACArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	if (bShooting)
	{
		CurTime +=DeltaTime;

		if (CurTime >= LifeTime)
		{
			bShooting=false;
			SetMesh(false);
			SetCollision(false);
			EndTrail();
		}

		Velocity.Z += Gravity * DeltaTime;

		//새로 추가한 부분 이상하면 여기를 삭제하셈
		FVector NextLocation = GetActorLocation() + Velocity * DeltaTime;

		SetActorLocation(/*GetActorLocation() + Velocity * DeltaTime*/ NextLocation);

		//FVector Dir = (NextLocation - GetActorLocation()).GetSafeNormal();

		//FRotator Rot = FRotationMatrix::MakeFromX(Dir).Rotator();
		//SetActorRotation(Rot);
	}
}

void ACArrow::SetMesh(bool bValue)
{
	ArrowMesh->SetVisibility(bValue);

	CurTime =0.0f;
}

void ACArrow::SetCollision(bool bValue)
{
	if (bValue)
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ACArrow::SetBool(bool bValue, FVector FirePos , float Alpha)
{
	bShooting = bValue;
	float Power = FMath::Lerp(MinPower,MaxPower, Alpha);
	FString Message = FString::Printf(TEXT("%f"),Power);
	GEngine->AddOnScreenDebugMessage(2, 10.0f, FColor::Black, Message);
	Velocity = FirePos * Power;
}

void ACArrow::ArrowOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bShooting = false;

	UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *OtherActor->GetName());

	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if (enemy)
	{
		enemy->OnDamageEnemy(DamageAmount);
	}

	EndTrail();
	
	SetMesh(false);
	SetCollision(false);
}

