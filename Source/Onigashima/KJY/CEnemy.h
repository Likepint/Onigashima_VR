﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CEnemy.generated.h"



UCLASS()
class ONIGASHIMA_API ACEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FSM)
	class UCEnemyFSM* FSM;

	UPROPERTY()
	class UCEnemyAnim* Anim;

public:
	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* EnemyComponent;
	//UPROPERTY(EditDefaultsOnly)
	//class UStaticMeshComponent* FirePosComp;

	//시퀀스 시도중
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death Sequence")
	 class ULevelSequence* DeathSequence;


public:	//시퀀스 재생 함수
	void PlayDeathSequence();

#pragma region CollisionSocketPart
UPROPERTY(EditDefaultsOnly)
class UBoxComponent* Collision_1;

UPROPERTY(EditDefaultsOnly)
class UBoxComponent* Collision_2;

UPROPERTY(EditDefaultsOnly)
class UBoxComponent* Collision_3;

UPROPERTY(EditDefaultsOnly)
class UBoxComponent* Collision_4;

UPROPERTY(EditDefaultsOnly)
class UBoxComponent* Collision_5;

UPROPERTY(EditDefaultsOnly)
class UBoxComponent* Collision_6;

UPROPERTY(EditDefaultsOnly)
class UBoxComponent* Collision_7;

UPROPERTY(EditDefaultsOnly)
class UBoxComponent* Collision_8;

UPROPERTY(EditDefaultsOnly)
class UBoxComponent* Collision_12;

UPROPERTY(EditDefaultsOnly)
class UBoxComponent* Collision_13;

UPROPERTY(EditDefaultsOnly)
class UBoxComponent* Collision_14;

UPROPERTY(EditDefaultsOnly)
class UBoxComponent* Collision_15;



#pragma endregion


	UPROPERTY(EditDefaultsOnly)
	class UArrowComponent* FireArrowComp;

	UPROPERTY(EditDefaultsOnly)
	class UArrowComponent* AimedFireArrowComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FireFactory)
	TSubclassOf<class ACFireBall> FireFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FireFactory)
	TSubclassOf<class ACAimedFireBall> AimedFireFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	int32 HP = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	int32 MaxHP = 20;

	//시퀀스 테스트할 때 썼음.
	bool bFortest = false;
	bool bSoundCheck = false;

#pragma region Fail
public: // 총알 오브젝트풀
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
	// int MaxBulletCnt = 40;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
	// TArray<class ACFireBall*> Magazine;
	//float fireSpawn = 4.f;
#pragma endregion Fail

public:
	float currentTime = 0.f;
	float MaxFireTime = 1.f;
	int MaxattackCount = 5;

	//불 3발 소환시 발사되도록 할 예정.
	int countAimedFire = 0;
	int maxAimedFire = 3;

public:
	void AttackFire();
	void AttackAimedFire();
	void OnDamageEnemy(int32 _value);
	void TestOnDamage();


	//실질적 깡통... 나중을 위해 주석처리만 해둠
/*
public:
	UFUNCTION(BlueprintCallable, Category = "Attack_Notify")
	void AttackStart();

	UFUNCTION(BluePrintCallable, Category = "Attack_Notify")
	void AttackEnd();
*/



public:	// 충돌처리
	UFUNCTION()	
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
