#include "PJS/Widgets/CUserWidget_CategorySlot.h"
#include "Global.h"
#include "Components/Image.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "PJS/Crafts/CItemBase.h"
#include "PJS/Components/CInventoryComponent.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "PJS/Widgets/CWidget_HUD.h"
#include "PJS/Widgets/CUserWidget_Craft.h"

void UCUserWidget_CategorySlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	CheckNull(Item);
	Thumbnail->SetBrushFromTexture(Item->GetDefaultObject<ACItemBase>()->GetItemStruct().Thumbnail);

	if (UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(GetOwningPlayerPawn()))
	{
		if (inventory->GetInventory().Find(Item))
			QuantityText->SetText(FText::AsNumber(inventory->GetInventory()[Item]));
		else
		{
			inventory->GetInventory().Add(Item, 0);
			QuantityText->SetText(FText::AsNumber(inventory->GetInventory()[Item]));
		}
	}

	Button->OnClicked.AddDynamic(this, &UCUserWidget_CategorySlot::Clicked);

}

void UCUserWidget_CategorySlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(GetOwningPlayerPawn());
	CheckNull(inventory);

	UCWidget_HUD* hud = Cast<UCWidget_HUD>(inventory->GetHUD());
	CheckNull(hud);
	
	UCUserWidget_Craft* craft = Cast<UCUserWidget_Craft>(hud->WBP_Craft);
	CheckNull(craft);

	if (IsHovered())
		craft->SetHoveredItem(this);
	else craft->SetHoveredItem(nullptr);

}

void UCUserWidget_CategorySlot::Clicked()
{
	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(GetOwningPlayerPawn());
	CheckNull(inventory);

	UCWidget_HUD* hud = Cast<UCWidget_HUD>(inventory->GetHUD());
	CheckNull(hud);

	UCUserWidget_Craft* craft = Cast<UCUserWidget_Craft>(hud->WBP_Craft);
	CheckNull(craft);

	craft->SetHoveredItem(this);

}
