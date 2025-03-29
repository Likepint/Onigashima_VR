// Fill out your copyright notice in the Description page of Project Settings.

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

public:
	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* EnemyComponent;
	//UPROPERTY(EditDefaultsOnly)
	//class UStaticMeshComponent* FirePosComp;


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


#pragma region CollisionSocketPart
/*
	UPROPERTY(EditDefaultsOnly)
	TArray<class UBoxComponent*> CollisionComponents;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
    FVector CollisionSize_1;

    UPROPERTY(EditDefaultsOnly, Category = "Collision")
    FVector CollisionSize_2;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
    FVector CollisionSize_3;

    UPROPERTY(EditDefaultsOnly, Category = "Collision")
    FVector CollisionSize_4;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
    FVector CollisionSize_5;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
    FVector CollisionSize_6;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
    FVector CollisionSize_7;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
    FVector CollisionSize_8;
	
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
    FVector CollisionSize_9;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
    FVector CollisionSize_10;
	
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
    FVector CollisionSize_11;
	
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
    FVector CollisionSize_12;
	
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
    FVector CollisionSize_13;
	
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
    FVector CollisionSize_14;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
    FVector CollisionSize_15;
*/
#pragma endregion

	UPROPERTY(EditDefaultsOnly)
	class UArrowComponent* ArrowComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FireFactory)
	TSubclassOf<class ACFireBall> FireFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FireFactory)
	TSubclassOf<class ACAimedFireBall> AimedFireFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	int32 HP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	int32 MaxHP = 20;

public:
	//FBodyInstance* boneJaw;

	float currentTime = 0.f;
	float MaxFireTime = 1.f;
	int MaxattackCount = 5;


public:
	void AttackFire();
	void AttackAimedFire();
	void OnDamageEnemy(int32 _value);


public:
	UFUNCTION(BlueprintCallable, Category = "Attack_Notify")
	void AttackStart();

	UFUNCTION(BluePrintCallable, Category = "Attack_Notify")
	void AttackEnd();

	

public:
	UFUNCTION()	
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



};
