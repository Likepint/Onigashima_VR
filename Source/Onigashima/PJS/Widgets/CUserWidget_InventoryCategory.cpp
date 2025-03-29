#include "PJS/Widgets/CUserWidget_InventoryCategory.h"
#include "Global.h"
#include "Components/TextBlock.h"
#include "PJS/Components/CInventoryComponent.h"
#include "PJS/Crafts/CItemBase.h"
#include "PJS/Widgets/CUserWidget_CategorySlot.h"
#include "Components/WrapBox.h"

void UCUserWidget_InventoryCategory::NativePreConstruct()
{
	Super::NativePreConstruct();

	CategoryTitle->SetText(FText::FromString(StaticEnum<EItemCategory>()->GetNameStringByValue(static_cast<int64>(Category))));

	AddCategory();

}

void UCUserWidget_InventoryCategory::AddCategory()
{
	CheckNull(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CheckNull(inventory);

	for (const auto& item : inventory->GetInventory())
	{
		if (Category != item.Key->GetItemStruct().category or !CategorySlot)
			continue;

		UCUserWidget_CategorySlot* category = CreateWidget<UCUserWidget_CategorySlot>(GetOwningPlayerPawn()->GetWorld(), CategorySlot);

		category->Item = item.Key;

		CategoryContainer->AddChildToWrapBox(category);
	}

}

void UCUserWidget_InventoryCategory::Refresh()
{
	CategoryContainer->ClearChildren();

	AddCategory();

}
