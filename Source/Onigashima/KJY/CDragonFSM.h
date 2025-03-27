// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CDragonFSM.generated.h"

UENUM()
enum class EDragonState: uint8
{
	Idle			UMETA (DisplayName = "Idle"),
	Move			UMETA (DisplayName = "Move"),
	AttackNum1		UMETA (DisplayName = "AttackNum1"),	// ºê·¹½º 1
	Dead			UMETA(DisplayName = "Dead")
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONIGASHIMA_API UCDragonFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCDragonFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
