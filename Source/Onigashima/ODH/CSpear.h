// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CItem.h"
#include "CSpear.generated.h"

UCLASS()
class ONIGASHIMA_API ACSpear : public ACItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACSpear();

	void SetMesh(bool bValue);

	void SetCollision(bool bValue);

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* CollisionComp;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void SpearOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
