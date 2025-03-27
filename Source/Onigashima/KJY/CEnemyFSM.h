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
enum class EAttackState : uint8	// ���� ������ ��
{
	//��� State�� �� State�� Base�� ���ƿ;� �� (�ش� Base���� MainBase(Idle)�� ����)
	ReturnBase	UMETA (DisplayName = "ReturnBase"),
	Breath		UMETA (DisplayName = "Breath"),
	Attack_1	UMETA (DisplayName = "Attack_1(Hand)"),
};


UENUM()
enum class EFlyState : uint8		// ���� ������ ��
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


private:	// ���� ����
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

private: // �ð� ���� ����
	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float idleDelayTime = 0.1f;
	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float attackDelayTime = 2.f;

	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float fireSpawn = 0.05f;

	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float currentTime = 0.f;


private: // Range ����
	UPROPERTY(EditAnywhere, Category = FSM)
	float attackRange = 900.f;
	UPROPERTY(EditAnywhere, Category = FSM)
	float breathRange = 900.f;
	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float searchRange = 3000.f;


private:
	// ���࿡ �ɸ��� �ð�
	const float AnimTime = 3.f;
	// �� ���� ä��� ������
	const int MaxLandCount = 3;
	// �� ���� ä��� ������

	const int MaxFlyCount = 3;
	// �������� ����.
	const int TotalAttKinds = 2;
	// ���� �������� ����.
	const int FlyTotalAttKinds = 2;


public:	//Count ����. ����ÿ��� ���
	// ���ݽø��� ���� ����ؼ� ���� ������ ��
	int randomAttack = 1;
	// ���� ���� Ƚ���� ���̸� ���� ���� ����.
	int attCount = 0;
	// ���� ���� Ƚ���� ���̸� ���� ���� ����.
	int attFlyCount = 0;


private:// State �Լ�
	void StartState();
	void IdleState();
	void MoveState();
	void FlyState();

	//Attack State �Լ�,
	void BreathState();		//�극�� ����
	void Attack_1State();	//�չ߰���

	//Fly �Լ�
	void StartFlyState();		//Fly ����
	void FlyIdleState();
	void FMoveState();
	void FlyBreathState();		//�극�� ����
	void FlyAttack_1State();	//�����...

	// Dead �Լ�
	void DeadState();

public:
	void TargetRotation();
	void OnAttackProcess();
	void EndAttackProcess();
	FVector SearchEnemy();
	void EndFlyState();

public:	//notify ����
	void StartHighFly_END();
	void End_Opening();
};
