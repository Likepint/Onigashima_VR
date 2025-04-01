#include "PJS/Crafts/CItem_Pick.h"
#include "Global.h"
#include "PJS/Crafts/CItem_Planks.h"
#include "PJS/Crafts/CItem_Stone.h"

ACItem_Pick::ACItem_Pick()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemStruct.Name = FName("Pick");

	ItemStruct.Description = FName("");

	ItemStruct.category = EItemCategory::Ammo;

	ItemStruct.bCraftable = true;

}

void ACItem_Pick::BeginPlay()
{
	Super::BeginPlay();

}

void ACItem_Pick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

