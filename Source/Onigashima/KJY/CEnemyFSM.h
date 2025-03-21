// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CEnemyFSM.generated.h"

UENUM()
enum class EEnemyState : uint8
{
	Idle	UMETA (DisplayName = "���"),
	Move	UMETA (DisplayName = "�̵�"),
	//�齺���� �ִϸ��̼� �ֳ� ����
	Attack	UMETA (DisplayName = "����"),
	Bite	UMETA (DisplayName = "����"),
	Breath	UMETA (DisplayName = "�극��"),
	//���� �ִϸ��̼ǿ�. ���� ���� ���δ� bool�� ó���� ����.
	Fly		UMETA (DisplayName = "����"),
	Dead	UMETA (DisplayName = "���"),
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
	//�չ߰���
	void AttackState();
	//���� ���� - ����� ����
	void BiteState();
	//�극�� ����
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


	// ���ݽø��� ���� ����ؼ� ���� ������ ��
	int randomAttack = 1;
	// ���� ���� Ƚ���� ���̸� ���� ���� ����
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
