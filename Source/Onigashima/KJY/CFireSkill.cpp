// Fill out your copyright notice in the Description page of Project Settings.


#include "KJY/CFireSkill.h"

// Sets default values
ACFireSkill::ACFireSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACFireSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACFireSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

