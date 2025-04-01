// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CItem.h"
#include "Sound/SoundCue.h"
#include "CAxe.generated.h"

UCLASS()
class ONIGASHIMA_API ACAxe : public ACItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACAxe();

	void SetMesh(bool bValue);

	void SetCollision(bool bValue);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* CollisionComp;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* ChopEffect;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundCue* AxeSound;

	UFUNCTION()
	void AxeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
