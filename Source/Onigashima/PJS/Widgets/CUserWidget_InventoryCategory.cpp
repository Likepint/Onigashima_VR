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

	CheckNull(GetOwningPlayerPawn());

	if (IsCraftedCategory)
	{
		for (const auto& item : CraftedItems)
		{
			UCUserWidget_CategorySlot* category = CreateWidget<UCUserWidget_CategorySlot>(GetOwningPlayerPawn()->GetWorld(), CategorySlot);

			category->Item = item;

			CategoryContainer->AddChildToWrapBox(category);
		}
	}
	else
	{
		UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(GetOwningPlayerPawn());
		CheckNull(inventory);

		for (const auto& item : inventory->GetInventory())
		{
			if (Category != item.Key->GetDefaultObject<ACItemBase>()->GetItemStruct().category or !CategorySlot)
				continue;

			UCUserWidget_CategorySlot* category = CreateWidget<UCUserWidget_CategorySlot>(GetOwningPlayerPawn()->GetWorld(), CategorySlot);

			category->Item = item.Key;

			CategoryContainer->AddChildToWrapBox(category);
		}
	}

}

void UCUserWidget_InventoryCategory::AddCategory()
{
	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(GetOwningPlayerPawn());
	CheckNull(inventory);

	for (const auto& item : inventory->GetInventory())
	{
		if (Category != item.Key->GetDefaultObject<ACItemBase>()->GetItemStruct().category or !CategorySlot)
			continue;

		UCUserWidget_CategorySlot* category = CreateWidget<UCUserWidget_CategorySlot>(GetOwningPlayerPawn()->GetWorld(), CategorySlot);

		category->Item = item.Key;

		CategoryContainer->AddChildToWrapBox(category);
	}

}

void UCUserWidget_InventoryCategory::AddWrapBox()
{
	for (const auto& item : CraftedItems)
	{
		UCUserWidget_CategorySlot* category = CreateWidget<UCUserWidget_CategorySlot>(GetOwningPlayerPawn()->GetWorld(), CategorySlot);

		category->Item = item;

		CategoryContainer->AddChildToWrapBox(category);
	}

}

void UCUserWidget_InventoryCategory::Refresh()
{
	CategoryContainer->ClearChildren();

	//AddWrapBox();

	//AddCategory();

	if (IsCraftedCategory)
	{
		for (const auto& item : CraftedItems)
		{
			UCUserWidget_CategorySlot* category = CreateWidget<UCUserWidget_CategorySlot>(GetOwningPlayerPawn()->GetWorld(), CategorySlot);

			category->Item = item;

			CategoryContainer->AddChildToWrapBox(category);
		}
	}
	else
	{
		UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(GetOwningPlayerPawn());
		CheckNull(inventory);

		for (const auto& item : inventory->GetInventory())
		{
			if (Category != item.Key->GetDefaultObject<ACItemBase>()->GetItemStruct().category or !CategorySlot)
				continue;

			if (CraftedItems.Find(item.Key) != nullptr) continue;

			UCUserWidget_CategorySlot* category = CreateWidget<UCUserWidget_CategorySlot>(GetOwningPlayerPawn()->GetWorld(), CategorySlot);

			category->Item = item.Key;

			CategoryContainer->AddChildToWrapBox(category);
		}
	}

}
