// Fill out your copyright notice in the Description page of Project Settings.


#include "KJY/CEnemy.h"
#include "CEnemyFSM.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "CKJYDummy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "../ODH/VRPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "CAimedFireBall.h"
#include "CFireBall.h"
#include "CEnemyAnim.h"

#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneSequence.h"
#include "LevelSequenceActor.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "../ODH/CArrow.h"



// Sets default values
ACEnemy::ACEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	EnemyComponent = GetMesh();
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TmpBody(TEXT("/Script/Engine.SkeletalMesh'/Game/KJY/_Dragon8/Mesh/SK_Dragon8.SK_Dragon8'"));


	if (TmpBody.Succeeded())
	{
		EnemyComponent->SetSkeletalMesh(TmpBody.Object);
		EnemyComponent->SetRelativeRotation(FRotator(0, -90, 0));
		EnemyComponent->SetRelativeLocation(FVector(0, 0, -80));
	}

	//FirePosComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FireComp"));
	//FirePosComp->SetupAttachment(EnemyComponent, TEXT("FirePosition"));
	
	FireArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("FireArrowComp"));
	FireArrowComp->SetupAttachment(EnemyComponent, TEXT("FirePosition"));
	FireArrowComp->SetRelativeLocation(FVector(80,0,0));
	FireArrowComp->SetRelativeRotation(FRotator(0,80,0));

	AimedFireArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("AimedFireArrowComp"));
	AimedFireArrowComp->SetupAttachment(EnemyComponent, TEXT("FirePosition"));
	AimedFireArrowComp->SetRelativeLocation(FVector(200, 200, 0));
	AimedFireArrowComp->SetRelativeRotation(FRotator(0, 80, 0));


#pragma region CollisionSocketPart
	//================== 소켓 붙이는 파트
	Collision_1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision_1"));
	Collision_1->SetupAttachment(EnemyComponent, TEXT("Collision_1"));
	Collision_1->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Collision_2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision_2"));
	Collision_2->SetupAttachment(EnemyComponent, TEXT("Collision_2"));
	Collision_2->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Collision_3 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision_3"));
	Collision_3->SetupAttachment(EnemyComponent, TEXT("Collision_3"));
	Collision_3->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Collision_4 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision_4"));
	Collision_4->SetupAttachment(EnemyComponent, TEXT("Collision_4"));
	Collision_4->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Collision_5 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision_5"));
	Collision_5->SetupAttachment(EnemyComponent, TEXT("Collision_5"));
	Collision_5->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Collision_6 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision_6"));
	Collision_6->SetupAttachment(EnemyComponent, TEXT("Collision_6"));
	Collision_6->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Collision_7 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision_7"));
	Collision_7->SetupAttachment(EnemyComponent, TEXT("Collision_7"));
	Collision_7->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Collision_8 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision_8"));
	Collision_8->SetupAttachment(EnemyComponent, TEXT("Collision_8"));
	Collision_8->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);


	Collision_12 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision_12"));
	Collision_12->SetupAttachment(EnemyComponent, TEXT("Collision_12"));
	Collision_12->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Collision_13 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision_13"));
	Collision_13->SetupAttachment(EnemyComponent, TEXT("Collision_13"));
	Collision_13->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Collision_14 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision_14"));
	Collision_14->SetupAttachment(EnemyComponent, TEXT("Collision_14"));
	Collision_14->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Collision_15 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision_15"));
	Collision_15->SetupAttachment(EnemyComponent, TEXT("Collision_15"));
	Collision_15->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
#pragma endregion

#pragma region SetExtentBox
	// ========================= 박스 크기 설정 파트

	Collision_1->SetBoxExtent(FVector(60.f, 50.f, 50.f));

	Collision_2->SetBoxExtent(FVector(100.f, 50.f, 50.f));
	Collision_3->SetBoxExtent(FVector(270.f, 180.f, 200.f));
	Collision_4->SetBoxExtent(FVector(50.f, 130.f, 50.f));
	Collision_5->SetBoxExtent(FVector(400.f, 210.f, 50.f));
	Collision_6->SetBoxExtent(FVector(50.f, 130.f, 50.f));
	Collision_7->SetBoxExtent(FVector(400.f, 210.f, 50.f));
	Collision_8->SetBoxExtent(FVector(100.f, 50.f, 30.f));

	Collision_12->SetBoxExtent(FVector(130.f, 50.f, 50.f));
	Collision_13->SetBoxExtent(FVector(130.f, 50.f, 50.f));
	Collision_14->SetBoxExtent(FVector(130.f, 50.f, 50.f));
	Collision_15->SetBoxExtent(FVector(130.f, 50.f, 50.f));

	Collision_5->SetRelativeLocation(FVector(20.f, 0.f, 0.f));
	Collision_7->SetRelativeLocation(FVector(20.f, 0.f, 0.f));
#pragma endregion



	FSM = CreateDefaultSubobject<UCEnemyFSM>(TEXT("FSM"));


	ConstructorHelpers::FClassFinder<UAnimInstance>tmpAnim(TEXT("LevelSequence'/Game/KJY/Level/Sequence/Dragon_Dead_SQ/Dragon_Dead_SQRoot.Dragon_Dead_SQRoot'"));

	if (tmpAnim.Succeeded()) {
		EnemyComponent->SetAnimInstanceClass(tmpAnim.Class);
	}

	USkeletalMeshComponent* SkeletalMeshComp = GetMesh();
	if (SkeletalMeshComp)
	{
		// 폴리 충돌 활성화
		SkeletalMeshComp->bEnablePerPolyCollision = true;
		SkeletalMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		SkeletalMeshComp->SetCollisionResponseToAllChannels(ECR_Block);
	}
		SkeletalMeshComp->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnOverlapBegin);


		static ConstructorHelpers::FObjectFinder<ULevelSequence> DeathSeqAsset(TEXT("LevelSequence'/Game/KJY/Level/Sequence/Dragon_Dead_SQ/Dragon_Dead_SQRoot.Dragon_Dead_SQRoot'"));

		if (DeathSeqAsset.Succeeded())
		{
			DeathSequence = DeathSeqAsset.Object;
		}

}

// Called when the game starts or when spawned
void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	HP = MaxHP;


	//  UWorld* world = GetWorld();
	//  if (DeathSequence != nullptr && world != nullptr)
	//  {
	//  	ALevelSequenceActor* OutActor = nullptr;
	//  	ULevelSequencePlayer::CreateLevelSequencePlayer(world, DeathSequence, FMovieSceneSequencePlaybackSettings(), // // utActor);
	//  
	//  }




	/*
	Anim = Cast<UCEnemyAnim>(this->GetMesh()->GetAnimInstance());


	for (int i = 0; i< MaxBulletCnt; ++i)
	{
		FActorSpawnParameters spawnParams;

		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ACFireBall* bulletFireBall = GetWorld()->SpawnActor<ACFireBall>(FireFactory, spawnParams);

		bulletFireBall->SetActivateFireBall(false);

		Magazine.Add(bulletFireBall);

	}
	*/

}

// Called every frame
void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// currentTime += DeltaTime;
	// 
	//  if (currentTime >= 2.f && bFortest == false)
	//  {
	//  	bFortest = true;
	//  	PlayDeathSequence();
	//  }

	// if (!Anim->bIsBreath){ return; }
	// 
	// currentTime += DeltaTime;
	// 
	// if (currentTime > fireSpawn) 
	// {
	// 	AttackFire();
	// 	currentTime = 0.f;
	// }
	// 
	// else{ AttackFire(); }
}

// Called to bind functionality to input
void ACEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}


void ACEnemy::AttackFire()
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
   
	FTransform FirePos = FireArrowComp->GetComponentTransform();
	GetWorld()->SpawnActor<ACFireBall>(FireFactory, FirePos, spawnParams);
	/*
	   bool FindResult = false;

	   FTransform t = FireArrowComp->GetComponentTransform();


	   for (int i = 0; i < Magazine.Num(); ++i)
	   {
		   //UE_LOG(LogTemp, Warning, TEXT("Bullet : %d"),i);
		   if (!Magazine[i]->MeshComp->GetVisibleFlag())
		   {
			   t.SetScale3D(Magazine[i]->MeshComp->GetComponentScale());
			   FindResult = true;

			   Magazine[i]->SetActivateFireBall(true);
			   Magazine[i]->SetActorTransform(t);

			   //소리 재생 파트
			   break;
		   }
	   }

	   if (!FindResult) { UE_LOG(LogTemp, Warning, TEXT("총알이 없는데용")); }
	
	*/
	
	++countAimedFire;
}


void ACEnemy::AttackAimedFire()
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;

	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform FirePos = AimedFireArrowComp->GetComponentTransform();
	GetWorld()->SpawnActor<ACAimedFireBall>(AimedFireFactory, FirePos, spawnParams);

}

void ACEnemy::OnDamageEnemy(int32 _value)
{
	this->HP -= _value;

	if (HP <= 0)
	{
		HP = 0;
		this->FSM->ImDead();
		PlayDeathSequence();
	}

}




void ACEnemy::TestOnDamage()
{
	this->OnDamageEnemy(MaxHP);
}

void ACEnemy::PlayDeathSequence()
{
	UWorld* world = GetWorld();
	if (world == nullptr) { return; }

	if (DeathSequence)
	{
		// 시퀀스 플레이어 생성
		ULevelSequencePlayer* SequencePlayer = nullptr;

		// 시퀀스를 현재 월드에서 재생
		FMovieSceneSequencePlaybackSettings Settings;

		ALevelSequenceActor* OutActor = nullptr;

		SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			world, DeathSequence, Settings, OutActor);

		if (SequencePlayer)
		{
			SequencePlayer->Play(); // 시퀀스 재생
		}
	}


}

/*
void ACEnemy::AttackStart()
{


}

void ACEnemy::AttackEnd()
{
//	GetWorld()->SweepMultiByProfile(OutOverlaps, this->FirePos, T.GetLocation(), T.GetRotation(), FName(TEXT("Pawn")), //FCollisionShape::MakeSphere(50.0f));
//
//
//	for (const FHitResult& e : OutOverlaps){
//		UE_LOG(LogTemp, Warning, TEXT("Collision !!! %s"), 
//		*e.GetActor()->GetFullName(), *e.GetComponent()->GetFullName());
//	}
//
//	UE_LOG(LogTemp, Warning, TEXT("StartPos !!! X : % f, Y : % f, Z : % f"), T.GetLocation().X, T.GetLocation().Y, //T.GetLocation().Z);
//
//	DrawDebugLine(GetWorld(), this->FirePos, T.GetLocation(), FColor::Emerald, true, -1, 0, 10);

}
*/



void ACEnemy::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACArrow* target = Cast<ACArrow>(OtherActor);	//에로우에 맞는거 만들기

	if (target) // 단해야 체력 계수 바꾸고 싶으면 말해
	{
		UE_LOG(LogTemp,Warning,TEXT("Overlaped"));	
		OnDamageEnemy(5);
	}
	
	if (target != nullptr)
	{

	}
	

}

