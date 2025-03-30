// 03.21 - 공격 패턴 수행시에는 Roatation 기능 삭제 (들어가 있으면 공격을 피할 수가 없을듯)
// 03.22 - 평타 공격 패턴이 하나뿐이라 Bite 삭제. 일단 두 개 만들기로 (시간 봐서 돌진공격 추가)
// 03.23 - 비행상태랑 일반 상태랑 제법 달라서 State를 분리하는게 나을지도?
//			ㄴ 분리했더니 IsAttack 필요 없어짐. 지움.
// 03.23 - 비행할때 좌표가 아래에 고정으로 있다 ㅠㅠ (IsFalling이 안됨...) 
//			ㄴ일단 ISFly로 비행상태 체크하기로
// 03.23 - 비행 공격마다 높이가 다르다... High / Low로 분리하거나 루트본 끌어치기 배워야 될 것 같음...


#include "KJY/CEnemyFSM.h"
#include "CEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "CKJYDummy.h"
#include "CEnemyAnim.h"

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

	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), AVRPlayer::StaticClass());

	if (!actor) { return; }
	target = Cast<AVRPlayer>(actor);

	enemy = Cast< ACEnemy>(GetOwner());

	if (!enemy) { return; }
	Anim = Cast<UCEnemyAnim>(enemy->GetMesh()->GetAnimInstance());


	// 혹시 모를 초기화
	randomAttack = FMath::RandRange(1, TotalAttKinds);
	attCount = 0;


}


// Called every frame
void UCEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//상태 체크


#pragma region LogMessageState
	FString logMsgState = UEnum::GetValueAsString(mState);
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, logMsgState);

	FString logMsgAtt = UEnum::GetValueAsString(mAttState);
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Green, logMsgAtt);

	FString logMsgFly = UEnum::GetValueAsString(mFlyState);
	GEngine->AddOnScreenDebugMessage(2, 1, FColor::Blue, logMsgFly);
#pragma endregion

	//스테이트 변경
	switch (mState)
	{
	case EEnemyState::Sleep		 : { SleepState();	}	break;
	case EEnemyState::Start		 : { StartState();	}	break;
	case EEnemyState::Idle		 : { IdleState();	}	break;
	case EEnemyState::Move		 : { MoveState();	}	break;
	case EEnemyState::Attack	 : {  }	break;
	case EEnemyState::Dead		 : { DeadState();	}	break;
	case EEnemyState::Fly		 : { FlyState ();	}	break;
	case EEnemyState::FlyAtt	 : {  }	break;
	}

	switch (mAttState)
	{
	case EAttackState::ReturnBase	: {  }	break;
	case EAttackState::Breath		: { BreathState();	}	break;
	case EAttackState::Attack_1		: { Attack_1State();}	break;

	default: break;
	}

	switch (mFlyState)
	{
	case EFlyState::ReturnBase		: {  }	break;
	case EFlyState::StartFly		: { StartFlyState();	}	break;
	case EFlyState::FlyIdle			: { FlyIdleState();		}	break;
	case EFlyState::FMove			: { FMoveState();		}	break;

	case EFlyState::FBreath			: { FlyBreathState(); }	break;
	case EFlyState::FAttack_1		: { FlyAttack_1State(); }	break;
	case EFlyState::FEndFly			: { /*EndFlyState();*/ }	break;
	default: break;
	}
}

void UCEnemyFSM::SleepState()
{
	mState = EEnemyState::Sleep;
	Anim->eAnimState = mState;

	FVector dir = SearchEnemy();

	if (dir.Size() < searchRange) { Anim->bIsDetect = true; }
}

void UCEnemyFSM::StartState()
{
	mState = EEnemyState::Start;
	Anim->eAnimState = mState;

}


// 대기 모션
void UCEnemyFSM::IdleState()
{
	//적 탐지 프로세스

	FVector dir = SearchEnemy();

	AActor* newplayer = UGameplayStatics::GetActorOfClass(GetWorld(), AVRPlayer::StaticClass());
	if (!newplayer) { return; }

	currentTime += GetWorld()->DeltaTimeSeconds;
	 

	if (attCount >= MaxFlyCount) {
		mState = EEnemyState::Fly;
		Anim->eAnimState = mState;
		attCount = 0;

		return;
	}

//if (currentTime < idleDelayTime) { return; }

	if (dir.Size() < attackRange) {
		OnAttackProcess();
		currentTime = 0.f;

		return;
	}

	// 임시 조건 : dir까지의 거리가 탐색 범위보다 좁음
	if (dir.Size() < searchRange){
		mState = EEnemyState::Move;
		Anim->eAnimState = mState;

		currentTime = 0.f;
	}


}


void UCEnemyFSM::MoveState()
{
	TargetRotation();
	FVector dir = SearchEnemy();
	enemy->AddMovementInput(dir);

	if (dir.Size() < attackRange) {
		OnAttackProcess();
	}

}


void UCEnemyFSM::FlyState()
{
	if (Anim->bIsStartFly == true)
	{
		mFlyState = EFlyState::StartFly;
		Anim->eFlyState = mFlyState;
	}

}

// 브레스 사용 모션
void UCEnemyFSM::BreathState()
{
	if (!Anim->bIsBreath) { return; }

	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime > fireSpawn) 
	{
		enemy->AttackFire();
		currentTime = 0.f;
	}
}


//앞발 공격 모션
void UCEnemyFSM::Attack_1State()
{

	/*
	
	//시간이 흐르다가 일정 시간 경과시
	currentTime += GetWorld()->DeltaTimeSeconds;

	//IdleState로 변경
	if ( currentTime > attackDelayTime){
		currentTime = 0.f;
		EndAttackProcess();
	}
	
	*/
}

//================================================================================================
//================================================================================================

//비행 시작 모션
void UCEnemyFSM::StartFlyState()
{
	Anim->bIsFly = true;
}


void UCEnemyFSM::FlyIdleState()
{
	UE_LOG(LogTemp, Warning, TEXT("111111111111"));

	//적 탐지 프로세스
	currentTime += GetWorld()->DeltaTimeSeconds;


// if (currentTime < idleDelayTime) { return; }

	FVector dir = SearchEnemy();

	if (dir.Size() < breathRange) {
		OnAttackProcess();
		return;
	}

	if (attFlyCount >= MaxLandCount)
	{
		mFlyState = EFlyState::FEndFly;
		Anim->eFlyState = mFlyState;

		attFlyCount = 0;
		return;
	}

	/*
	if (dir.Size() < searchRange) {
		mFlyState = EFlyState::FMove;
		Anim->eFlyState = mFlyState;
	}
	*/

	currentTime = 0.f;
}

void UCEnemyFSM::FMoveState()
{
	TargetRotation();
	FVector dir = SearchEnemy();
	enemy->AddMovementInput(dir);

	if (dir.Size() < attackRange) {
		OnAttackProcess();
	}

}

void UCEnemyFSM::FlyBreathState()
{
	Anim->bIsAttack = true;
}



void UCEnemyFSM::FlyAttack_1State()
{
	Anim->bIsAttack = true;
}

// 착지 시점 / 착지 시작할 때를 다르게 해야 할 듯?
void UCEnemyFSM::EndFlyState()
{
	mState = EEnemyState::Idle;
	Anim->eAnimState = mState;

	mFlyState = EFlyState::ReturnBase;
	Anim->eAnimState = mState;

	Anim->bIsFly = false;
}

//==============================================

//사망 모션
void UCEnemyFSM::DeadState()
{
	
}
//==============================================


//타겟 방향으로 로테이션
void UCEnemyFSM::TargetRotation()
{
	FVector dir = SearchEnemy();

	FRotator TargetRotation = dir.Rotation();
	FRotator NewRotation	= enemy->GetActorRotation();

	NewRotation.Yaw = TargetRotation.Yaw;
	enemy->SetActorRotation(NewRotation);
}


//공격 패턴 랜덤 결정해주는 파트
void UCEnemyFSM::OnAttackProcess()
{

	//UE_LOG(LogTemp, Warning, TEXT("2222222"));

	if (Anim->bIsFly == true){
		
		mFlyState = EFlyState::FBreath;
		Anim->eFlyState = mFlyState;

		//Attack_1에 착지 모션이 있어서 착지 자체를 이쪽으로 하면 자연스럽게 땅으로 내려옴
		if (attFlyCount > MaxFlyCount){
			mFlyState = EFlyState::FAttack_1;
			Anim->eFlyState = mFlyState;
		}

		
		mState = EEnemyState::FlyAtt;
		Anim->eAnimState = mState;

		switch (randomAttack)
		{
		case 1:
			mFlyState = EFlyState::FBreath;
			Anim->eFlyState = mFlyState;
			break;

		case 2:
			mFlyState = EFlyState::FAttack_1;
			Anim->eFlyState = mFlyState;
			break;
		}
		
		return;
	}


	else {
		mState = EEnemyState::Attack;
		Anim->eAnimState = mState;

		mAttState = EAttackState::Breath;
		Anim->eAttackState = mAttState;
		//테스트를 위해 브레스만 나오게 막아둠.
		/*
		switch (randomAttack)
		{
		case 1:
			mAttState = EAttackState::Breath;
			Anim->eAttackState = mAttState;
			break;

		case 2:
			mAttState = EAttackState::Attack_1;
			Anim->eAttackState = mAttState;
			break;
		}
		*/
	}


}

//IsFly 상태에 따라 다름.
void UCEnemyFSM::EndAttackProcess()
{
	Anim->bIsAttack = false;

	//비행일 경우
	if (Anim->bIsFly == true){
		//랜덤 돌려서 Breath, Attack_1 결정
		++attFlyCount;

		int saveRand = randomAttack;
		randomAttack = FMath::RandRange(1, FlyTotalAttKinds);

		while (saveRand == randomAttack) { randomAttack = FMath::RandRange(1, FlyTotalAttKinds); }

		mFlyState = EFlyState::FlyIdle;
		Anim->eFlyState = mFlyState;
		return;
	}

	//비행이 아닐 경우
	else{
		//랜덤 돌려서 Breath, Attack_1 결정
		++attCount;

		int saveRand = randomAttack;
		randomAttack = FMath::RandRange(1, TotalAttKinds);
		
		//같은 애니메이션 연속으로 안 나오게 하기
		while (saveRand == randomAttack) { randomAttack = FMath::RandRange(1, TotalAttKinds); }

		mState = EEnemyState::Idle;
		Anim->eAnimState = mState;

		mAttState = EAttackState::ReturnBase;
		Anim->eAttackState = mAttState;
	}

}


//적 탐지 / 적 방향 리턴
FVector UCEnemyFSM::SearchEnemy()
{
	if ( target == nullptr || enemy == nullptr) { return FVector::ZeroVector; }

	FVector destination		= target->GetActorLocation();
	FVector dir				= destination - enemy->GetActorLocation();

	return dir;
}

//죽었을 경우 사용하는 함수
void UCEnemyFSM::ImDead()
{
	Anim->bIsDead = true;
	mState = EEnemyState::Dead;
	if (Anim) { Anim->eAnimState = mState; }
}


//==================== Notify 관련 함수들 ====================

void UCEnemyFSM::StartHighFly_END()
{	
	UE_LOG(LogTemp, Warning, TEXT("AAAAAAA"));

	mFlyState = EFlyState::FlyIdle;
	if(Anim){ Anim->eFlyState = mFlyState; }

}

void UCEnemyFSM::End_Opening()
{
	mState = EEnemyState::Idle;
	if(Anim){ Anim->eAnimState = mState; }
}

void UCEnemyFSM::Sleep_END()
{
	mState = EEnemyState::Start;
	if (Anim) { Anim->eAnimState = mState; }
}



