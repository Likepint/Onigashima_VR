// 03.21 - ���� ���� ����ÿ��� Roatation ��� ���� (�� ������ ������ ���� ���� ������)
// 03.22 - ��Ÿ ���� ������ �ϳ����̶� Bite ����. �ϴ� �� �� ������ (�ð� ���� �������� �߰�)
// 03.23 - ������¶� �Ϲ� ���¶� ���� �޶� State�� �и��ϴ°� ��������?
//			�� �и��ߴ��� IsAttack �ʿ� ������. ����.
// 03.23 - �����Ҷ� ��ǥ�� �Ʒ��� �������� �ִ� �Ф� (IsFalling�� �ȵ�...) 
//			���ϴ� ISFly�� ������� üũ�ϱ��
// 03.23 - ���� ���ݸ��� ���̰� �ٸ���... High / Low�� �и��ϰų� ��Ʈ�� ����ġ�� ����� �� �� ����...

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

	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ACKJYDummy::StaticClass());
	
	if (!actor) { return; }
	target = Cast<ACKJYDummy>(actor);

	enemy = Cast< ACEnemy>(GetOwner());
	
	if (!enemy) { return; }
	Anim = Cast<UCEnemyAnim>(enemy->GetMesh()->GetAnimInstance());


	// Ȥ�� �� �ʱ�ȭ
	randomAttack = FMath::RandRange(1, TotalAttKinds);
	attCount = 0;
}


// Called every frame
void UCEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//���� üũ


#pragma region LogMessageState
	FString logMsgState = UEnum::GetValueAsString(mState);
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, logMsgState);

	FString logMsgAtt = UEnum::GetValueAsString(mAttState);
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Green, logMsgAtt);

	FString logMsgFly = UEnum::GetValueAsString(mFlyState);
	GEngine->AddOnScreenDebugMessage(2, 1, FColor::Blue, logMsgFly);
#pragma endregion

	//������Ʈ ����
	switch (mState)
	{
	case EEnemyState::Idle		 : { IdleState();		}	break;
	case EEnemyState::Move		 : { MoveState();		}	break;
	case EEnemyState::Attack	 : {  }	break;
	case EEnemyState::Dead		 : { DeadState();		}	break;
	case EEnemyState::Fly		 : { FlyState ();		}	break;
	case EEnemyState::FlyAtt	 : {  }	break;
	}

	switch (mAttState)
	{
	case EAttackState::ReturnBase	: {  }	break;
	case EAttackState::Breath		: { BreathState();		}	break;
	case EAttackState::Attack_1		: { Attack_1State();	}	break;

	default: break;
	}

	switch (mFlyState)
	{
	case EFlyState::ReturnBase		: {  }	break;
	//case EFlyState::StartFly		: { /*StartFlyState();*/ }	break;
	case EFlyState::FlyIdle			: { FlyIdleState();		 }	break;
	case EFlyState::FMove			: { FMoveState();		 }	break;

	case EFlyState::FBreath			: { FlyBreathState();	 }	break;
	case EFlyState::FAttack_1		: { FlyAttack_1State();  }	break;
	case EFlyState::FEndFly			: { EndFlyState();		 }	break;
	default: break;
	}
}

// ��� ���
void UCEnemyFSM::IdleState()
{
	//�� Ž�� ���μ���
	FVector dir = SearchEnemy();
	currentTime += GetWorld()->DeltaTimeSeconds;
	
	if (attCount >= MaxFlyCount){
		mState = EEnemyState::Fly;
		Anim->eAnimState = mState;
		attCount = 0;

		return;
	}

if (currentTime < idleDelayTime) { return; }

	if (dir.Size() < attackRange) {
		OnAttackProcess();
		currentTime = 0.f;

		return;
	}

	// �ӽ� ���� : dir������ �Ÿ��� Ž�� �������� ����
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
	Anim->IsFly = true;
	mFlyState = EFlyState::StartFly;
	Anim->eFlyState = mFlyState;
}

// �극�� ��� ���
void UCEnemyFSM::BreathState()
{


}


//�չ� ���� ���
void UCEnemyFSM::Attack_1State()
{

	/*
	
	//�ð��� �帣�ٰ� ���� �ð� �����
	currentTime += GetWorld()->DeltaTimeSeconds;

	//IdleState�� ����
	if ( currentTime > attackDelayTime){
		currentTime = 0.f;
		EndAttackProcess();
	}
	
	*/

}

//================================================================================================
//================================================================================================
//���� ���� ���
void UCEnemyFSM::StartFlyState()
{


}


void UCEnemyFSM::FlyIdleState()
{
	UE_LOG(LogTemp, Warning, TEXT("111111111111"));

	//�� Ž�� ���μ���
	FVector dir = SearchEnemy();
	currentTime += GetWorld()->DeltaTimeSeconds;


	//���� Ƚ�� ä��� �������� ����
	if (attFlyCount >= MaxLandCount) {
		mFlyState = EFlyState::FEndFly;
		Anim->eFlyState = mFlyState;
		
		return;
	}


if (currentTime < idleDelayTime) { return; }

	if (dir.Size() < attackRange) {
		OnAttackProcess();
		return;
	}

	// �ӽ� ���� : currentTime�� IdleTime���� Ŀ���� ��� && dir������ �Ÿ��� Ž�� �������� ����
	if (dir.Size() < searchRange) {
		mFlyState = EFlyState::FMove;
		Anim->eFlyState = mFlyState;

		currentTime = 0.f;
	}


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
	//�ð��� �帣�ٰ� ���� �ð� �����
	currentTime += GetWorld()->DeltaTimeSeconds;

	//IdleState�� ����
	if (currentTime > attackDelayTime) {
		EndAttackProcess();
		currentTime = 0.f;
	}
}



void UCEnemyFSM::FlyAttack_1State()
{
	//�ð��� �帣�ٰ� ���� �ð� �����
	currentTime += GetWorld()->DeltaTimeSeconds;

	//IdleState�� ����
	if (currentTime > attackDelayTime) {
		EndAttackProcess();
	}
}

// ���� ���� / ���� ������ ���� �ٸ��� �ؾ� �� ��?
void UCEnemyFSM::EndFlyState()
{

	/*
	mState = EEnemyState::Idle;
	Anim->eAnimState = mState;
	*/

	Anim->IsFly = false;
}

//==============================================

//��� ���
void UCEnemyFSM::DeadState()
{
	
}
//==============================================


//Ÿ�� �������� �����̼�
void UCEnemyFSM::TargetRotation()
{
	FVector dir = SearchEnemy();

	FRotator TargetRotation = dir.Rotation();
	FRotator NewRotation	= enemy->GetActorRotation();

	NewRotation.Yaw = TargetRotation.Yaw;
	enemy->SetActorRotation(NewRotation);
}


//���� ���� ���� �������ִ� ��Ʈ
void UCEnemyFSM::OnAttackProcess()
{

	//UE_LOG(LogTemp, Warning, TEXT("2222222"));

	if (Anim->IsFly == true){
		
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
	}


}

//IsFly ���¿� ���� �ٸ�.
void UCEnemyFSM::EndAttackProcess()
{

	//������ ���
	if (Anim->IsFly == true){
		//���� ������ Breath, Attack_1 ����
		++attFlyCount;

		randomAttack = FMath::RandRange(1, FlyTotalAttKinds);

		mFlyState = EFlyState::FlyIdle;
		Anim->eFlyState = mFlyState;
		
		return;
	}

	//������ �ƴ� ���
	else{
		//���� ������ Breath, Attack_1 ����
		++attCount;

		randomAttack = FMath::RandRange(1, TotalAttKinds);

		mState = EEnemyState::Idle;
		Anim->eAnimState = mState;

		mAttState = EAttackState::ReturnBase;
		Anim->eAttackState = mAttState;
	}

}


//�� Ž�� / �� ���� ����
FVector UCEnemyFSM::SearchEnemy()
{
	if ( target == nullptr || enemy == nullptr) { return FVector::ZeroVector; }

	FVector destination		= target->GetActorLocation();
	FVector dir				= destination - enemy->GetActorLocation();

	return dir;
}


//==================== Notify ���� �Լ��� ====================

void UCEnemyFSM::StartHighFly_END()
{
	mFlyState = EFlyState::FlyIdle;
	Anim->eFlyState = mFlyState;
}

