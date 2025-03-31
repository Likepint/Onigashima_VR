// Fill out your copyright notice in the Description page of Project Settings.


#include "KJY/CAimedFireBall.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../ODH/VRPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../PJS/Components/CBaseComponent.h"
#include "CEnemy.h"
#include "Components/SceneComponent.h"
#include "../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
#include "CFireSkill.h"

// Sets default values
ACAimedFireBall::ACAimedFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;

	//VFX 고치면 주석처리 고대로 살리면 됨2
	/*
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("AimedSceneComp"));
	RootComponent = SceneRoot;

	AimedFireBallEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("AimedFireBallNiagara"));
	AimedFireBallEffect->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("/Game/KJY/EnergyBallVFX/Niagara/NS_AimedFireBall.NS_AimedFireBall"));
	if (NiagaraAsset.Succeeded())
	{
		AimedFireBallEffect->SetAsset(NiagaraAsset.Object);
	}


	AimedSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("AimedSphereComp"));
	AimedSphereComp->SetupAttachment(SceneRoot);
	AimedSphereComp->SetSphereRadius(100.f);
	AimedSphereComp->SetRelativeScale3D(FVector(0.6f));


	AimedSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ACAimedFireBall::AimedOnOverlapBegin);
	*/

	AimedSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = AimedSphereComp;
	AimedSphereComp->SetSphereRadius(100.f);
	AimedSphereComp->SetRelativeScale3D(FVector(0.6f));

	AimedMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	AimedMeshComp->SetupAttachment(AimedSphereComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tmpMesh(TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/ArcadeEditorSphere.ArcadeEditorSphere'"));
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

	AActor* pActor = UGameplayStatics::GetActorOfClass(GetWorld(), AVRPlayer::StaticClass());
	if (!pActor) { return; }

	Aimedplayer = Cast<AVRPlayer>(pActor);	//AVRPlayer로 바꾸기


	AActor* eActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACEnemy::StaticClass());
	if (!eActor) { return; }
	enemy = Cast<ACEnemy>(eActor);
	
	maxFire = enemy->maxAimedFire;
}

// Called every frame
void ACAimedFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (enemy != nullptr && enemy->countAimedFire >= maxFire)
	{ 
		if (Aimedplayer != nullptr) { dir = (destination - this->GetActorLocation()).GetSafeNormal(); }
		else { dir = GetActorForwardVector(); }
	}

	//발사 직전까지 조준하고 싶음
	else 
	{ 
		dir = FVector(0); 
		destination = Aimedplayer->GetActorLocation();
	}



	currentTime += DeltaTime;

	Pos = this->GetActorLocation() + dir * speed * DeltaTime;
	SetActorLocation(Pos);


	if (currentTime > lifeSpan) { this->Destroy(); }
	if (destination.Size() <= 10) { this->Destroy(); }
	
}

void ACAimedFireBall::AimedOnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AVRPlayer* targetPlayer = Cast<AVRPlayer>(OtherActor);

	if (targetPlayer != nullptr)
	{
		targetPlayer->OnDamagePlayer(1);
		this->Destroy();

		//SetActivateFireBall(false);
	}


	UCBaseComponent* targetBuildComp = Cast<UCBaseComponent>(OtherActor);
	if (targetBuildComp != nullptr)
	{
		targetBuildComp->DestroyComponent();	//체력 감소로 변경.
		//SetActivateFireBall(false);
		this->Destroy();
	}

	ACFireSkill* checkSelf = Cast<ACFireSkill>(OtherActor);
	if (checkSelf != OtherActor)
	{
		
	}
}

