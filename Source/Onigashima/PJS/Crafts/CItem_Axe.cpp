#include "PJS/Crafts/CItem_Axe.h"
#include "Global.h"
#include "PJS/Crafts/CItem_Planks.h"
#include "PJS/Crafts/CItem_Stone.h"

ACItem_Axe::ACItem_Axe()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemStruct.Name = FName("Axe");

	ItemStruct.Description = FName("");

	ItemStruct.category = EItemCategory::Ammo;

	ItemStruct.bCraftable = true;

}

void ACItem_Axe::BeginPlay()
{
	Super::BeginPlay();

}

void ACItem_Axe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
