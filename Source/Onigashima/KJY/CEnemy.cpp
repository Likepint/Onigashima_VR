// Fill out your copyright notice in the Description page of Project Settings.


#include "KJY/CEnemy.h"
#include "CEnemyFSM.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "CKJYDummy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


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
	
	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	ArrowComp->SetupAttachment(EnemyComponent, TEXT("FirePosition"));
	ArrowComp->SetRelativeLocation(FVector(80,0,0));
	ArrowComp->SetRelativeRotation(FRotator(0,80,0));


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



#pragma region CollisionSocketPart_Gone
/*
	for (int32 i = 1; i <= 15; i++)
	{
		FName ComponentName = FName(*FString::Printf(TEXT("Collision_%d"), i));
		UBoxComponent* NewCollision = CreateDefaultSubobject<UBoxComponent>(ComponentName);
		NewCollision->SetupAttachment(EnemyComponent, *FString::Printf(TEXT("Collision_%d"), i));
		NewCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CollisionComponents.Add(NewCollision); // 배열에 추가
	}


	CollisionSize_1 = FVector(60.f, 50.f, 50.f);
	CollisionSize_2 = FVector(100.f, 50.f, 50.f);
	CollisionSize_3 = FVector(50.f, 50.f, 200.f);
	CollisionSize_4 = FVector(50.f, 50.f, 200.f);
	CollisionSize_5 = FVector(200.f, 180.f, 200.f);
	CollisionSize_6 = FVector(200.f, 180.f, 200.f);

	if (CollisionComponents.Num() >= 15)
	{

		CollisionComponents[0]->SetBoxExtent(CollisionSize_1);
		CollisionComponents[1]->SetBoxExtent(CollisionSize_2);
		CollisionComponents[2]->SetBoxExtent(CollisionSize_3);
		CollisionComponents[3]->SetBoxExtent(CollisionSize_4);
		CollisionComponents[4]->SetBoxExtent(CollisionSize_5);
		CollisionComponents[5]->SetBoxExtent(CollisionSize_6);
		CollisionComponents[6]->SetBoxExtent(CollisionSize_7);
		CollisionComponents[7]->SetBoxExtent(CollisionSize_8);
		CollisionComponents[8]->SetBoxExtent(CollisionSize_9);
		CollisionComponents[9]->SetBoxExtent(CollisionSize_10);
		CollisionComponents[10]->SetBoxExtent(CollisionSize_11);
		CollisionComponents[11]->SetBoxExtent(CollisionSize_12);
		CollisionComponents[12]->SetBoxExtent(CollisionSize_13);
		CollisionComponents[13]->SetBoxExtent(CollisionSize_14);
		CollisionComponents[14]->SetBoxExtent(CollisionSize_15);
	}

	//Collision_1->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	*/
	
#pragma endregion



	FSM = CreateDefaultSubobject<UCEnemyFSM>(TEXT("FSM"));


	ConstructorHelpers::FClassFinder<UAnimInstance>tmpAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/KJY/ABP_Enemy.ABP_Enemy'"));

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
	
}

// Called when the game starts or when spawned
void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	HP = MaxHP;
	
	//FirePosComp->GetAttachParent();


}

// Called every frame
void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void ACEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ACEnemy::AttackFire()
{

	//UE_LOG(LogTemp,Warning,TEXT("whyNoT...."));
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	//if (currentTime > MaxFireTime){
	//FTransform FirePos = FirePosComp->GetComponentTransform();
	FTransform FirePos = ArrowComp->GetComponentTransform();
	//GetWorld()->SpawnActor<ACFireBall>(FireFactory, FirePos, spawnParams);

	UE_LOG(LogTemp, Warning, TEXT("Fire!!!!"));
	//}


	//시작지점 X, Y, Z 지점 좌표 찍어보자
	//UE_LOG(LogTemp, Warning, TEXT("FirePos !!! X : % f, Y : % f, Z : % f"), FirePos.GetLocation().X, FirePos.GetLocation().Y, FirePos.GetLocation().Z);
}


void ACEnemy::OnDamageEnemy(int32 _value)
{
	this->HP -= _value;
}

void ACEnemy::AttackStart()
{


}

void ACEnemy::AttackEnd()
{


	
	/*
	GetWorld()->SweepMultiByProfile(OutOverlaps, this->FirePos, T.GetLocation(), T.GetRotation(), FName(TEXT("Pawn")), FCollisionShape::MakeSphere(50.0f));


	for (const FHitResult& e : OutOverlaps){
		UE_LOG(LogTemp, Warning, TEXT("Collision !!! %s"), 
		*e.GetActor()->GetFullName(), *e.GetComponent()->GetFullName());
	}

	UE_LOG(LogTemp, Warning, TEXT("StartPos !!! X : % f, Y : % f, Z : % f"), T.GetLocation().X, T.GetLocation().Y, T.GetLocation().Z);

	DrawDebugLine(GetWorld(), this->FirePos, T.GetLocation(), FColor::Emerald, true, -1, 0, 10);

	*/
	
}



void ACEnemy::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 충돌한 액터를 AEnemyActor 클래스로 변환!
	ACKJYDummy* target = Cast<ACKJYDummy>(OtherActor);

	if (target) {	UE_LOG(LogTemp,Warning,TEXT("Overlaped"));	}
	
	if (target != nullptr)
	{
		target->Destroy();
		this->Destroy();
	}
	

}

