// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAimedFireBall.generated.h"

UCLASS()
class ONIGASHIMA_API ACAimedFireBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACAimedFireBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere)
    class USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComponent;

    //UFUNCTION()
    //void LaunchProjectile(AVRPlayer* Target);

private:
	UPROPERTY(VisibleAnywhere, Category = AimedFSM)
	class AVRPlayer* Aimedplayer;

	UPROPERTY(VisibleAnywhere, Category = AimedFSM)
	class ACEnemy* enemy;

private:
	float currentTime = 0.f;
	float lifeSpan = 5.f;
	int maxFire = 0;

public:

	UPROPERTY(VisibleAnywhere, Category = AimedMovement)
	class USphereComponent* AimedSphereComp;

	UPROPERTY(VisibleAnywhere, Category = AimedMovement)
	class UStaticMeshComponent* AimedMeshComp;

	FVector dir;
	FVector dir2;
	FVector Pos;

	float timePowerA = 0.f;
	float timePowerB = 0.f;

	float speed = 3000.f;

	FVector destination;


public:
	UFUNCTION()
	void AimedOnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
