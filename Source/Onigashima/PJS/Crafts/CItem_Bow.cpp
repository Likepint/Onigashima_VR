#include "PJS/Crafts/CItem_Bow.h"
#include "Global.h"
#include "PJS/Crafts/CItem_Planks.h"
#include "PJS/Crafts/CItem_Stone.h"

ACItem_Bow::ACItem_Bow()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemStruct.Name = FName("Bow");

	ItemStruct.Description = FName("");

	ItemStruct.category = EItemCategory::Ammo;

	ItemStruct.bCraftable = true;

}

void ACItem_Bow::BeginPlay()
{
	Super::BeginPlay();

}

void ACItem_Bow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

