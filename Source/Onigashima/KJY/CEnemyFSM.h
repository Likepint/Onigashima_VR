// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CEnemyFSM.generated.h"

UENUM()
enum class EEnemyState : uint8
{
	Idle	UMETA (DisplayName = "대기"),
	Move	UMETA (DisplayName = "이동"),
	//백스텝은 애니메이션 있나 보고
	Attack	UMETA (DisplayName = "공격"),
	Bite	UMETA (DisplayName = "물기"),
	Breath	UMETA (DisplayName = "브레스"),
	//비행 애니메이션용. 실제 비행 여부는 bool값 처리할 예정.
	Fly		UMETA (DisplayName = "비행"),
	Dead	UMETA (DisplayName = "사망"),
	Endstate
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FSM")
	EEnemyState mState = EEnemyState::Idle;

	void IdleState();
	void MoveState();
	//앞발공격
	void AttackState();
	//물기 공격 - 비행시 돌진
	void BiteState();
	//브레스 공격
	void BreathState();
	void FlyState();
	void DeadState();

public:


	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float idleDelayTime = 0.5f;
	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float attackDelyaTime = 2.f;
	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float currentTime = 0.f;

	
	UPROPERTY(EditAnywhere, Category = FSM)
	float attackRange = 200.f;
	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float searchRange = 2000.f;


	// 공격시마다 새로 계산해서 랜덤 공격을 함
	int randomAttack = 1;
	// 일정 공격 횟수가 쌓이면 비행 패턴 돌입
	int attCount = 0;

	UPROPERTY(VisibleAnywhere, Category = FSM)
	class ACKJYDummy* target;

	UPROPERTY()
	class ACEnemy* me;

public:
	void TargetRotation();
	void OnAttackProcess();
	FVector SearchEnemy();
};
