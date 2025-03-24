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
//기본적으로 eAnimState 사용, Fly나 Attack일때만 아래 두 개 붙여줌
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	EEnemyState eAnimState	 = EEnemyState::Idle;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	EAttackState eAttackState = EAttackState::ReturnBase;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	EFlyState eFlyState = EFlyState::ReturnBase;


public: // bool체크 변수 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EnemyAnim_bool)
	bool IsFly = false;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EnemyAnim_bool)
	//bool IsAttack = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EnemyAnim_bool)
	bool IsDead = false;


public:	//수치값
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EnemyAnimState)
	float speed = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EnemyAnimState)
	float direction = 0.f;

public:	// AnimNotify 관련
	UFUNCTION()
	void AnimNotify_StartHighFly_END();
	UFUNCTION()
	void AnimNotify_ATT1_END();
	UFUNCTION()
	void AnimNotify_Breath_END();
};
