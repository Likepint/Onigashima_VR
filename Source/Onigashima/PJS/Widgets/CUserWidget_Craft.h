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

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget))
	class UCUserWidget_InventoryCategory* Turret;

public:
	void RefreshInventory();

};
