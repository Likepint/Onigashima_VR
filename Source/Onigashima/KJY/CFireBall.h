// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CFireSkill.h"
#include "CFireBall.generated.h"

UCLASS()
class ONIGASHIMA_API ACFireBall : public ACFireSkill
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACFireBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere, Category = FSM)
	class AVRPlayer* player;


	float currentTime = 0.f;
	float lifeSpan = 4.f;

	FVector dir;

public:
	/*
	UPROPERTY(VisibleAnywhere, Category = Movement)
	class UProjectileMovementComponent* MovementComp;
	*/

	UPROPERTY(VisibleAnywhere, Category = Movement)
	class USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	class UStaticMeshComponent* MeshComp;

	float speed = 1000.f;

	FVector destination;



public:	//오브젝트 풀 관련 함수
	void SetActivateFireBall(bool _bValue);

public:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
