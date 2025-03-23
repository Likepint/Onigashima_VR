// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CVRPlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class ONIGASHIMA_API UCVRPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ActionValue)
	float PoseAlphaGrsap = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ActionValue)
	float PoseAlphaIndexCurl = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ActionValue)
	bool bMirror = false;
};
