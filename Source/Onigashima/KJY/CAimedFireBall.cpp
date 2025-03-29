// Fill out your copyright notice in the Description page of Project Settings.


#include "KJY/CAimedFireBall.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../ODH/VRPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ACAimedFireBall::ACAimedFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AimedSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = AimedSphereComp;
	AimedSphereComp->SetSphereRadius(100.f);
	AimedSphereComp->SetRelativeScale3D(FVector(0.6f));

	AimedMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	AimedMeshComp->SetupAttachment(AimedSphereComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tmpMesh(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (tmpMesh.Succeeded())
	{
		AimedMeshComp->SetStaticMesh(tmpMesh.Object);
	}


	AimedSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ACAimedFireBall::AimedOnOverlapBegin);


}

// Called when the game starts or when spawned
void ACAimedFireBall::BeginPlay()
{
	Super::BeginPlay();

	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), AVRPlayer::StaticClass());
	if (!actor) { return; }

	Aimedplayer = Cast<AVRPlayer>(actor);	//AVRPlayer로 바꾸기
	destination = Aimedplayer->GetActorLocation();
	
}

// Called every frame
void ACAimedFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Aimedplayer != nullptr) { dir = (destination - this->GetActorLocation()).GetSafeNormal(); }
	else { dir = GetActorForwardVector(); }


	currentTime += DeltaTime;

	Pos = this->GetActorLocation() + dir * speed * DeltaTime;
	SetActorLocation(Pos);


	if (currentTime > lifeSpan) { this->Destroy(); }
	
	
}

void ACAimedFireBall::AimedOnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AVRPlayer* targetPlayer = Cast<AVRPlayer>(OtherActor);

	if (targetPlayer != nullptr)
	{
		targetPlayer->OnDamagePlayer(1); 	//플레이어 체력 감소 함수로 변경
		this		->Destroy();
	}

}

