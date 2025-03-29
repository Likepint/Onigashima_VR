#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_CategorySlot.generated.h"

UCLASS()
class ONIGASHIMA_API UCUserWidget_CategorySlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget))
	class UImage* Thumbnail;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* QuantityText;

protected:
	virtual void NativePreConstruct() override;
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true))
	class ACItemBase* Item;

};
