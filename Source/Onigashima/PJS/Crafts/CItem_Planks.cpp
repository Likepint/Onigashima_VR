#include "PJS/Crafts/CItem_Planks.h"
#include "Global.h"

ACItem_Planks::ACItem_Planks()
{
	PrimaryActorTick.bCanEverTick = true;

	Name = FName("Planks");

	Description = FName("");

	category = EItemCategory::Parts;

}

void ACItem_Planks::BeginPlay()
{
	Super::BeginPlay();

}

void ACItem_Planks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
