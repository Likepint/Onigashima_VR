#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_HUD.generated.h"

UCLASS()
class ONIGASHIMA_API UCWidget_HUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* HUD;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget))
	class UUserWidget* WBP_Craft;
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void ToggleCraftMenu();
	void ToggleCraftMenu_Implementation();

};
