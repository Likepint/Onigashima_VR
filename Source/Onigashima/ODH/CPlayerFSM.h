// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPlayerFSM.generated.h"

// UENUM()
// enum class EItemState :uint8
// {
// 	NoItem UMETA(DisplayName = "�Ǽ�"),
// 	SetSpear UMETA(DisplayName = "â"),
// 	SetPick UMETA(DisplayName = "���"),
// 	SetAxe UMETA(DisplayName = "����"),
// 	SetBow UMETA(DisplayName = "Ȱ")
// };

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONIGASHIMA_API UCPlayerFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPlayerFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
// 	EItemState mItemState = EItemState::NoItem;
};
