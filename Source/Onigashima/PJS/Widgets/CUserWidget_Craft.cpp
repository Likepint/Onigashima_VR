#include "PJS/Widgets/CUserWidget_Craft.h"
#include "Global.h"
#include "PJS/Crafts/CItemBase.h"
#include "PJS/Crafts/CItem_Bow.h"
#include "PJS/Widgets/CUserWidget_InventoryCategory.h"
#include "PJS/Widgets/CUserWidget_CategorySlot.h"
#include "PJS/Components/CInventoryComponent.h"

void UCUserWidget_Craft::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UCUserWidget_Craft::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UCUserWidget_Craft::RefreshInventory()
{
	Parts->Refresh();
	Ammo->Refresh();

}

bool UCUserWidget_Craft::CheckRecipe(TMap<TSubclassOf<class ACItemBase>, int32> InItems)
{
	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(GetOwningPlayerPawn());
	CheckNullResult(inventory, false);

	bool bComplete = true;

	for (const auto& item : InItems)
	{
		FQueryResult result;

		if (inventory->GetInventory().Find(item.Key))
			 result = inventory->QueryInventory(item.Key, item.Value);

		if (!result.bSuccess)
			return false;
	}

	return bComplete;
}

void UCUserWidget_Craft::RemoveIngredients(TMap<TSubclassOf<class ACItemBase>, int32> InIngredients)
{
	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(GetOwningPlayerPawn());
	CheckNull(inventory);

	for (auto& Ingredient : InIngredients)
	{
		if (inventory->GetInventory().Find(Ingredient.Key))
			inventory->RemoveFromInventory(Ingredient.Key, Ingredient.Value);
	}

}

void UCUserWidget_Craft::CraftItem()
{
	CheckNull(HoveredItem);

	CLog::Print(HoveredItem->GetName());

	TMap<TSubclassOf<class ACItemBase>, int32> recipe = HoveredItem->Item->GetDefaultObject<ACItemBase>()->GetItemStruct().Recipe;
	if (recipe.IsEmpty()) return;

	bool b = CheckRecipe(recipe);
	if (!b) return;

	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(GetOwningPlayerPawn());
	CheckNull(inventory);

	inventory->AddToInventory(HoveredItem->Item, 1);

	RemoveIngredients(recipe);

	RefreshInventory();

}
