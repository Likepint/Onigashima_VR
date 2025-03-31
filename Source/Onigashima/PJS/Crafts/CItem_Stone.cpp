#include "PJS/Crafts/CItem_Stone.h"
#include "Global.h"

ACItem_Stone::ACItem_Stone()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemStruct.Name = FName("Stone");

	ItemStruct.Description = FName("");

	ItemStruct.category = EItemCategory::Parts;

}

void ACItem_Stone::BeginPlay()
{
	Super::BeginPlay();

}

void ACItem_Stone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
