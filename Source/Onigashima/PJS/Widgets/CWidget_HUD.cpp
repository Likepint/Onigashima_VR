#include "PJS/Widgets/CWidget_HUD.h"
#include "Global.h"
#include "GameFramework/PlayerController.h"

void UCWidget_HUD::ToggleCraftMenu_Implementation()
{
	if (IsVisible())
	{
		SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
		GetOwningPlayer()->bShowMouseCursor = false;
	}
	else
	{
		SetVisibility(ESlateVisibility::Visible);

		FInputModeGameAndUI mode;
		mode.SetWidgetToFocus(GetSlateWidgetFromName(FName("WBP_Craft")));
		mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		mode.SetHideCursorDuringCapture(true);
		GetOwningPlayer()->SetInputMode(mode);
		GetOwningPlayer()->bShowMouseCursor = true;
	}

}
