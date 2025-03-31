// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CItem.h"
#include "CPick.generated.h"

UCLASS()
class ONIGASHIMA_API ACPick : public ACItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPick();

	void SetMesh(bool bValue);

	void SetCollision(bool bValue);

public:	
	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* CollisionComp;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* StoneEffect;

	UFUNCTION()
	void PickOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
