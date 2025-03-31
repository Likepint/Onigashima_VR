#include "PJS/Crafts/CItemBase.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "PJS/Components/CInventoryComponent.h"
#include "PJS/Widgets/CWidget_HUD.h"
#include "PJS/Widgets/CUserWidget_Craft.h"

ACItemBase::ACItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UStaticMeshComponent>(this, &StaticMesh, "StaticMesh", RootComponent);

}

void ACItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACItemBase::LookAt(ACharacter* OwnerCharacter)
{

}

void ACItemBase::InteractWith(ACharacter* OwnerCharacter)
{
	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(OwnerCharacter);
	CheckNull(inventory);

	inventory->AddToInventory(this->GetClass(), 1);
	
	UCWidget_HUD* hud = Cast<UCWidget_HUD>(inventory->GetHUD());
	CheckNull(hud);

	hud->WBP_Craft->RefreshInventory();
	
	Destroy();

}
