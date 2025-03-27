// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CEnemyFSM.generated.h"

UENUM()
enum class EEnemyState : uint8
{
	Start		UMETA(DisplayName = "Start"),
	Idle		UMETA (DisplayName = "Idle"),
	Move		UMETA (DisplayName = "Move"),
	Attack		UMETA (DisplayName = "Attack"),
	Dead		UMETA(DisplayName = "Dead"),
	Fly			UMETA (DisplayName = "Fly"),
	FlyAtt		UMETA(DisplayName = "FlyAtt"),
};


UENUM()
enum class EAttackState : uint8	// 공격 상태일 때
{
	//모든 State는 각 State의 Base로 돌아와야 함 (해당 Base에서 MainBase(Idle)로 복귀)
	ReturnBase	UMETA (DisplayName = "ReturnBase"),
	Breath		UMETA (DisplayName = "Breath"),
	Attack_1	UMETA (DisplayName = "Attack_1(Hand)"),
};


UENUM()
enum class EFlyState : uint8		// 비행 상태일 때
{
	ReturnBase		UMETA(DisplayName =  "FReturnBase"),
	StartFly		UMETA(DisplayName  = "FStart"),
	FlyIdle			UMETA (DisplayName = "FIdle"),
	FMove			UMETA(DisplayName =  "FMove"),
	FBreath			UMETA (DisplayName = "FBreath"),
	FAttack_1		UMETA (DisplayName = "FAttack_1(Rand)"),
	FEndFly			UMETA(DisplayName =  "FEnd"),
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONIGASHIMA_API UCEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCEnemyFSM();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:	// 세팅 관련
	UPROPERTY(VisibleAnywhere, Category = FSM)
	class ACKJYDummy* target;
	UPROPERTY()
	class ACEnemy* enemy;
	UPROPERTY()
	class UCEnemyAnim* Anim;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FSM")
	EEnemyState mState = EEnemyState::Start;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FSM")
	EAttackState mAttState = EAttackState::ReturnBase;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FSM")
	EFlyState mFlyState = EFlyState::ReturnBase;

private: // 시간 관련 변수
	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float idleDelayTime = 0.1f;
	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float attackDelayTime = 2.f;

	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float fireSpawn = 0.05f;

	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float currentTime = 0.f;


private: // Range 변수
	UPROPERTY(EditAnywhere, Category = FSM)
	float attackRange = 900.f;
	UPROPERTY(EditAnywhere, Category = FSM)
	float breathRange = 900.f;
	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float searchRange = 3000.f;


private:
	// 비행에 걸리는 시간
	const float AnimTime = 3.f;
	// 이 값을 채우면 착륙함
	const int MaxLandCount = 3;
	// 이 값을 채우면 비행함

	const int MaxFlyCount = 3;
	// 랜덤공격 갯수.
	const int TotalAttKinds = 2;
	// 비행 랜덤공격 갯수.
	const int FlyTotalAttKinds = 2;


public:	//Count 변수. 비행시에도 사용
	// 공격시마다 새로 계산해서 랜덤 공격을 함
	int randomAttack = 1;
	// 일정 공격 횟수가 쌓이면 비행 패턴 돌입.
	int attCount = 0;
	// 일정 공격 횟수가 쌓이면 비행 패턴 돌입.
	int attFlyCount = 0;


private:// State 함수
	void StartState();
	void IdleState();
	void MoveState();
	void FlyState();

	//Attack State 함수,
	void BreathState();		//브레스 공격
	void Attack_1State();	//앞발공격

	//Fly 함수
	void StartFlyState();		//Fly 시작
	void FlyIdleState();
	void FMoveState();
	void FlyBreathState();		//브레스 공격
	void FlyAttack_1State();	//고민중...

	// Dead 함수
	void DeadState();

public:
	void TargetRotation();
	void OnAttackProcess();
	void EndAttackProcess();
	FVector SearchEnemy();
	void EndFlyState();

public:	//notify 관련
	void StartHighFly_END();
	void End_Opening();
};
