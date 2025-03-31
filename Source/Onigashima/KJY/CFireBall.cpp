// Fill out your copyright notice in the Description page of Project Settings.


#include "KJY/CFireBall.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CKJYDummy.h"
#include "Kismet/GameplayStatics.h"
#include "CEnemy.h"
#include "../ODH/VRPlayer.h"
#include "../PJS/Components/CBaseComponent.h"
#include "Components/SceneComponent.h"
#include "../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"

// Sets default values
ACFireBall::ACFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//VFX 고치면 주석처리 고대로 살리면 됨

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneRoot;

	FireBallEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireBallNiagara"));
	FireBallEffect->SetupAttachment(RootComponent);

	
	 static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("/Game/KJY/EnergyBallVFX/Niagara/NS_FireBall.NS_FireBall"));
	 if (NiagaraAsset.Succeeded())
	 {
	 	FireBallEffect->SetAsset(NiagaraAsset.Object);
	 }

	
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(SceneRoot);
	SphereComp->SetSphereRadius(100.f);
	SphereComp->SetRelativeScale3D(FVector(0.6f));

	 /*
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = SphereComp;
	SphereComp->SetSphereRadius(100.f);
	SphereComp->SetRelativeScale3D(FVector(0.6f));


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(SphereComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tmpMesh(TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/ArcadeEditorSphere.ArcadeEditorSphere'"));
	if (tmpMesh.Succeeded())
	{
		MeshComp->SetStaticMesh(tmpMesh.Object);
	}
	*/

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ACFireBall::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ACFireBall::BeginPlay()
{
	Super::BeginPlay();


	if (FireBallEffect){ FireBallEffect->Activate(true); }
	
	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), AVRPlayer::StaticClass());
	if (!actor) { return; }

	player = Cast<AVRPlayer>(actor);	//AVRPlayer로 바꾸기
	destination = player->GetActorLocation();

	//==================================
	FActorSpawnParameters params;

	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

}


// Called every frame
void ACFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	dir = GetActorForwardVector();
	FVector Pos = this->GetActorLocation() + dir* speed * DeltaTime;

	SetActorLocation(Pos);

	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime > lifeSpan) { this->Destroy();}

	//if (currentTime > lifeSpan) { this->SetActivateFireBall(false); }

}



void ACFireBall::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AVRPlayer* targetPlayer = Cast<AVRPlayer>(OtherActor);
	if (targetPlayer != nullptr)
	{
		targetPlayer->OnDamagePlayer(1);
		//SetActivateFireBall(false);
		this->Destroy();
	}


	UCBaseComponent* targetBuildComp = Cast<UCBaseComponent>(OtherActor);
	if (targetBuildComp != nullptr)
	{
		targetBuildComp->DestroyComponent();	//체력 감소로 변경.
		//SetActivateFireBall(false);
		this->Destroy();
	}

	// ACFireBall* checkSelf = Cast<ACFireBall>(OtherActor);
	// if (checkSelf != OtherActor)
	// {
	// 	this->Destroy();
	// }

}
