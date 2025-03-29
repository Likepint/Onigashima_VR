#include "PJS/Widgets/CUserWidget_Craft.h"
#include "Global.h"
#include "PJS/Widgets/CUserWidget_InventoryCategory.h"

void UCUserWidget_Craft::RefreshInventory()
{
	TArray<UCUserWidget_InventoryCategory*> categories = { Parts, Ammo, Turret };

	for (auto& category : categories)
		category->Refresh();

}
