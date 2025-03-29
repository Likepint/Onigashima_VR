// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CArrow.generated.h"

UCLASS()
class ONIGASHIMA_API ACArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACArrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetMesh(bool bValue);

	void SetCollision(bool bValue);

	void SetBool(bool bValue, FVector FirePos, float Alpha);

	//C++에서 선언하지만 블루프린트에서 내용을 구현해야함
	//그대신 C++에서 함수를 부를 수 있음
	UFUNCTION(BlueprintImplementableEvent, Category = Trail)
	void StartTrail();

	UFUNCTION(BlueprintImplementableEvent, Category = Trail)
	void EndTrail();


	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* ArrowMesh;

	UPROPERTY(EditAnywhere, Category = Arrow)
	FVector Velocity;

	float Gravity = -980.0f;

private:
	int32 DamageAmount = 1;

	float MinPower = 200;
	float MaxPower = 2000;

	float CurTime = 0.0f;
	float LifeTime = 5.5f;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* Collision;

	bool bShooting = false;

	UFUNCTION()
	void ArrowOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
