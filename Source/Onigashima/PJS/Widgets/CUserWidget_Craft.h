#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Craft.generated.h"

UCLASS()
class ONIGASHIMA_API UCUserWidget_Craft : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget))
	class UCUserWidget_InventoryCategory* Parts;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget))
	class UCUserWidget_InventoryCategory* Ammo;

protected:
	virtual void NativePreConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	FORCEINLINE class UCUserWidget_CategorySlot* GetHoveredItem() { return HoveredItem; }
	FORCEINLINE void SetHoveredItem(class UCUserWidget_CategorySlot* InItem) { HoveredItem = InItem; }

public:
	void RefreshInventory();

	bool CheckRecipe(TMap<TSubclassOf<class ACItemBase>, int32> InItems);

	void RemoveIngredients(TMap<TSubclassOf<class ACItemBase>, int32> InIngredients);

	void CraftItem();

private:
	class UCUserWidget_CategorySlot* HoveredItem;

};
