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

	class UCEnemyFSM* FSM;
public:
//기본적으로 eAnimState 사용, Fly나 Attack일때만 아래 두 개 붙여줌
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	EEnemyState eAnimState	 = EEnemyState::Sleep;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	EAttackState eAttackState = EAttackState::ReturnBase;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	EFlyState eFlyState = EFlyState::ReturnBase;
	                     

public: // bool체크 변수 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = EnemyAnim_bool)
	bool bIsFly = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = EnemyAnim_bool)
	bool bIsStartFly = true;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EnemyAnim_bool)
	//bool IsAttack = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = EnemyAnim_bool)
	bool bIsDead = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = EnemyAnim_bool)
	bool bIsDetect = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = EnemyAnim_bool)
	bool bIsBreath = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = EnemyAnim_bool)
	bool bIsAttack = false;


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
	UFUNCTION()
	void AnimNotify_FBreath_END();
	
	UFUNCTION()
	void AnimNotify_FAttack_END();
	/*
	UFUNCTION()
	void AnimNotify_AttackStart();
	*/
	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_Breath_Start();

	UFUNCTION()
	void AnimNotify_End_Opening();

	UFUNCTION()
	void AnimNotify_Spawn_AimedFireBall();

	UFUNCTION()
	void AnimNotify_Fly_END();

	UFUNCTION()
	void AnimNotify_Sleep_END();
	UFUNCTION()
	void AnimNotify_Select_ATT();
};
