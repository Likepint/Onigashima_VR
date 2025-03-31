// Fill out your copyright notice in the Description page of Project Settings.


#include "KJY/CEnemyAnim.h"
#include "CEnemy.h"

void UCEnemyAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	enemy = Cast<ACEnemy>(TryGetPawnOwner());
	if(!enemy) { return; }

	FSM = enemy->FindComponentByClass<UCEnemyFSM>();


	FVector velocity = enemy->GetVelocity();
	FVector forwardVector = enemy->GetActorForwardVector();

	
	speed = FVector::DotProduct(velocity, forwardVector);

	FVector rightVector = enemy->GetActorRightVector();
	direction = FVector::DotProduct(velocity, rightVector);
}


// ===================== 노티파이 추가하는 파트 =====================



void UCEnemyAnim::AnimNotify_StartHighFly_END()
{
	if (FSM) { FSM->StartHighFly_END(); }
	bIsStartFly = false;
}

void UCEnemyAnim::AnimNotify_ATT1_END()
{
	if (FSM) { FSM->EndAttackProcess(); }
}


void UCEnemyAnim::AnimNotify_Breath_Start()
{
	bIsBreath = true;
}
void UCEnemyAnim::AnimNotify_Breath_END()
{
	if (FSM) { FSM->EndAttackProcess();  }
	bIsBreath = false;
}




void UCEnemyAnim::AnimNotify_FBreath_END()
{
	bIsBreath = false;
}


void UCEnemyAnim::AnimNotify_FAttack_END()
{

	if (FSM) { FSM->EndAttackProcess(); }
}

/*
void UCEnemyAnim::AnimNotify_AttackStart()
{
	enemy->AttackStart();
}
*/

void UCEnemyAnim::AnimNotify_AttackEnd()
{
	if (FSM){ FSM ->EndAttackProcess(); }
}



void UCEnemyAnim::AnimNotify_End_Opening()
{
	if (FSM){ FSM->End_Opening(); }
}

void UCEnemyAnim::AnimNotify_Spawn_AimedFireBall()
{
	if (enemy) { enemy->AttackAimedFire(); }
}

void UCEnemyAnim::AnimNotify_Fly_END()
{
	if (FSM){ FSM->EndFlyState(); }

}

void UCEnemyAnim::AnimNotify_Sleep_END()
{
	if (FSM) { FSM->Sleep_END(); }
}

void UCEnemyAnim::AnimNotify_Select_ATT()
{
	if (FSM) { FSM->OnAttackProcess(); }
}

