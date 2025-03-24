// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CEnemyFSM.h"
#include "CEnemyAnim.generated.h"


UCLASS()
class ONIGASHIMA_API UCEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	class ACEnemy* enemy;

public:
//�⺻������ eAnimState ���, Fly�� Attack�϶��� �Ʒ� �� �� �ٿ���
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	EEnemyState eAnimState	 = EEnemyState::Idle;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	EAttackState eAttackState = EAttackState::ReturnBase;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	EFlyState eFlyState = EFlyState::ReturnBase;


public: // boolüũ ���� 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EnemyAnim_bool)
	bool IsFly = false;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EnemyAnim_bool)
	//bool IsAttack = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EnemyAnim_bool)
	bool IsDead = false;


public:	//��ġ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EnemyAnimState)
	float speed = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EnemyAnimState)
	float direction = 0.f;

public:	// AnimNotify ����
	UFUNCTION()
	void AnimNotify_StartHighFly_END();
	UFUNCTION()
	void AnimNotify_ATT1_END();
	UFUNCTION()
	void AnimNotify_Breath_END();
};
