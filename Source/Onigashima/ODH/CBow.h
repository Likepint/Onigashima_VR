// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CItem.h"
#include "CBow.generated.h"

UCLASS()
class ONIGASHIMA_API ACBow : public ACItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACBow();

	void SetMesh(bool bValue);

	void SetCollision(bool bValue);

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* CollisionComp;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly)
	class UArrowComponent* FirePos;
};
