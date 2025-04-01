// Fill out your copyright notice in the Description page of Project Settings.


#include "ODH/CItem.h"
#include "GameFramework/Character.h"

// Sets default values
ACItem::ACItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACItem::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

}

