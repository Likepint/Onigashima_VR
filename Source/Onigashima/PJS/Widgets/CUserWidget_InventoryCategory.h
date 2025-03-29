#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PJS/Crafts/CItemBase.h"
#include "CUserWidget_InventoryCategory.generated.h"

UCLASS()
class ONIGASHIMA_API UCUserWidget_InventoryCategory : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* CategoryTitle;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget))
	class UWrapBox* CategoryContainer;

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<class UCUserWidget_CategorySlot> CategorySlot;

protected:
	virtual void NativePreConstruct() override;

private:
	void AddCategory();

public:
	void Refresh();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EItemCategory Category = EItemCategory::MAX;

};
