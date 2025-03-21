// Fill out your copyright notice in the Description page of Project Settings.


#include "KJY/CEnemyFSM.h"
#include "CEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "CKJYDummy.h"

// Sets default values for this component's properties
UCEnemyFSM::UCEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ACKJYDummy::StaticClass());

	if (actor)
	{
		target = Cast<ACKJYDummy>(actor);
	}

	me = Cast< ACEnemy>(GetOwner());

}


// Called every frame
void UCEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//에러코드
	FString logMsg = UEnum::GetValueAsString(mState);
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, logMsg);

	//스테이트 변경
	switch (mState)
	{

	case EEnemyState::Idle	 : { IdleState(); }	break;
	case EEnemyState::Move	 : { MoveState(); }	break;
	case EEnemyState::Attack : { AttackState(); }break;
	case EEnemyState::Bite	 : { BiteState(); }	break;
	case EEnemyState::Breath : { BreathState(); }	break;
	case EEnemyState::Fly	 : { FlyState()	; }	break;
	case EEnemyState::Dead   : { IdleState(); }	break;

	}

}

void UCEnemyFSM::IdleState()
{
	//적 탐지 프로세스
	FVector dir = SearchEnemy();
	currentTime += GetWorld()->DeltaTimeSeconds;


	// 임시 조건 : currentTime이 IdleTime보다 커졌을 경우 && dir까지의 거리가 탐색 범위보다 좁음
	if (currentTime > idleDelayTime && dir.Size() < searchRange){
		mState = EEnemyState::Move;
		currentTime = 0.f;
	}
}



void UCEnemyFSM::MoveState()
{
	FVector dir = SearchEnemy();
	me->AddMovementInput(dir);

	if (dir.Size() < attackRange) {
		OnAttackProcess();
	}

}

void UCEnemyFSM::AttackState()
{
	//플레이어 방향으로 고개를 돌리고
	TargetRotation();

	//시간이 흐르다가 일정 시간 경과시
	currentTime += GetWorld()->DeltaTimeSeconds;

	//IdleState로 변경
	if ( currentTime > attackDelyaTime){
		mState = EEnemyState::Idle;
	}

}

void UCEnemyFSM::BiteState()
{
	//플레이어 방향으로 고개를 돌리고
	TargetRotation();

	//시간이 흐르다가 일정 시간 경과시
	currentTime += GetWorld()->DeltaTimeSeconds;

	//IdleState로 변경
	if (currentTime > attackDelyaTime) {
		mState = EEnemyState::Idle;
	}

}

void UCEnemyFSM::BreathState()
{
	//플레이어 방향으로 고개를 돌리고
	TargetRotation();

	//시간이 흐르다가 일정 시간 경과시
	currentTime += GetWorld()->DeltaTimeSeconds;

	//IdleState로 변경
	if (currentTime > attackDelyaTime) {
		mState = EEnemyState::Idle;
	}

}

//비행 시작
void UCEnemyFSM::FlyState()
{
}

//사망
void UCEnemyFSM::DeadState()
{
}

//==============================================

void UCEnemyFSM::TargetRotation()
{
	FVector dir = SearchEnemy();

	FRotator TargetRotation = dir.Rotation();
	FRotator NewRotation = me->GetActorRotation();

	NewRotation.Yaw = TargetRotation.Yaw;
	me->SetActorRotation(NewRotation);
}


void UCEnemyFSM::OnAttackProcess()
{

	//랜덤 돌려서 Attack, Bite, Breath
	randomAttack = FMath::RandRange(1,3);

	switch (randomAttack)
	{
	case 1: 
		mState = EEnemyState::Attack;
		break;
	case 2:
		mState = EEnemyState::Bite;
		break;
	case 3:
		mState = EEnemyState::Breath;
		break;
	}

}

FVector UCEnemyFSM::SearchEnemy()
{

	if (target == nullptr || me == nullptr) { return FVector::ZeroVector; }

	FVector destination = target->GetActorLocation();
	FVector dir = destination - me->GetActorLocation();

	 return dir;
}

