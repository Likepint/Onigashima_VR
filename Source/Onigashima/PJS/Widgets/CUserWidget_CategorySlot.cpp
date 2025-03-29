#include "PJS/Widgets/CUserWidget_CategorySlot.h"
#include "Global.h"
#include "Components/Image.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "PJS/Crafts/CItemBase.h"
#include "PJS/Components/CInventoryComponent.h"
#include "Components/TextBlock.h"

void UCUserWidget_CategorySlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	CheckNull(Item);
	Thumbnail->SetBrushFromTexture(Item->GetItemStruct().Thumbnail);

	if (UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(GetOwningPlayerPawn()))
		QuantityText->SetText(FText::AsNumber(*inventory->GetInventory().Find(Item)));

}
