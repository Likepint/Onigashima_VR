// Fill out your copyright notice in the Description page of Project Settings.


#include "KJY/CEnemyAnim.h"
#include "CEnemy.h"

void UCEnemyAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	enemy = Cast<ACEnemy>(TryGetPawnOwner());
	if(!enemy) { return; }


	// speed, direction ����ϴ� ��Ʈ (����� ����������... �����ϱ�)
	FVector velocity = enemy->GetVelocity();
	FVector forwardVector = enemy->GetActorForwardVector();


	speed = FVector::DotProduct(velocity, forwardVector);


	FVector rightVector = enemy->GetActorRightVector();
	direction = FVector::DotProduct(velocity, rightVector);
}


// ===================== ��Ƽ���� �߰��ϴ� ��Ʈ =====================



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
}

