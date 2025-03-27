// Fill out your copyright notice in the Description page of Project Settings.


#include "KJY/CEnemyAnim.h"
#include "CEnemy.h"

void UCEnemyAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	enemy = Cast<ACEnemy>(TryGetPawnOwner());
	if(!enemy) { return; }


	FVector velocity = enemy->GetVelocity();
	FVector forwardVector = enemy->GetActorForwardVector();


	speed = FVector::DotProduct(velocity, forwardVector);


	FVector rightVector = enemy->GetActorRightVector();
	direction = FVector::DotProduct(velocity, rightVector);
}


// ===================== 노티파이 추가하는 파트 =====================



void UCEnemyAnim::AnimNotify_StartHighFly_END()
{
	enemy->FSM->StartHighFly_END();
}

void UCEnemyAnim::AnimNotify_ATT1_END()
{
	enemy->FSM->EndAttackProcess();
}

void UCEnemyAnim::AnimNotify_Breath_END()
{
	enemy->FSM->EndAttackProcess();
	bIsBreath = false;
}

void UCEnemyAnim::AnimNotify_FBreath_END()
{
	enemy->FSM->EndAttackProcess();
	bIsBreath = false;
}

void UCEnemyAnim::AnimNotify_FAttack_END()
{

	enemy->FSM->EndFlyState();
}

void UCEnemyAnim::AnimNotify_AttackStart()
{
	enemy->AttackStart();
}

void UCEnemyAnim::AnimNotify_AttackEnd()
{
	enemy->AttackEnd();
}

void UCEnemyAnim::AnimNotify_Breath_Start()
{
	bIsBreath = true;


}

void UCEnemyAnim::AnimNotify_End_Opening()
{
	enemy->FSM->End_Opening();

}

