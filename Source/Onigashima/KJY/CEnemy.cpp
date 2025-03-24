// Fill out your copyright notice in the Description page of Project Settings.


#include "KJY/CEnemy.h"
#include "CEnemyFSM.h"

// Sets default values
ACEnemy::ACEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FSM = CreateDefaultSubobject<UCEnemyFSM>(TEXT("FSM"));

	ConstructorHelpers::FClassFinder<UAnimInstance>tmpAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/KJY/ABP_Enemy.ABP_Enemy'"));

	if ( tmpAnim.Succeeded() ){
		GetMesh()->SetAnimInstanceClass(tmpAnim.Class);
	}

}

// Called when the game starts or when spawned
void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

