#include "PJS/Components/CInventoryComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "PJS/Widgets/CWidget_HUD.h"
#include "PJS/Widgets/CUserWidget_Craft.h"
#include "Camera/CameraComponent.h"
#include "PJS/Crafts/CItemBase.h"

UCInventoryComponent::UCInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CHelpers::GetAsset<UInputAction>(&IA_Interact, TEXT("/Script/EnhancedInput.InputAction'/Game/PJS/Inputs/IA_Interact_PJS.IA_Interact_PJS'"));
	CHelpers::GetAsset<UInputAction>(&IA_Craft, TEXT("/Script/EnhancedInput.InputAction'/Game/PJS/Inputs/IA_Craft_PJS.IA_Craft_PJS'"));

}

void UCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	CheckNull(UI_HUD);
	HUD = CreateWidget<UUserWidget>(OwnerCharacter->GetWorld(), UI_HUD, FName("HUD"));

	HUD->AddToViewport();
	HUD->SetVisibility(ESlateVisibility::Hidden);

}

void UCInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckLookAt();

	CLog::Print(bShowInventory);

}

void UCInventoryComponent::OnBindEnhancedInputSystem(UEnhancedInputComponent* InEnhancedInput)
{
	InEnhancedInput->BindAction(IA_Interact, ETriggerEvent::Started, this, &UCInventoryComponent::Interact);
	InEnhancedInput->BindAction(IA_Craft, ETriggerEvent::Started, this, &UCInventoryComponent::OnCraft);

}

void UCInventoryComponent::Interact(const FInputActionValue& InVal)
{
	if (bShowInventory)
	{
		if (UCWidget_HUD* hud = Cast<UCWidget_HUD>(HUD))
			hud->WBP_Craft->CraftItem();
	}
	else
	{
		CheckNull(Target);

		Target->InteractWith(OwnerCharacter);
	}

}

void UCInventoryComponent::OnCraft(const FInputActionValue& InVal)
{
	if (UCWidget_HUD* hud = Cast<UCWidget_HUD>(HUD))
	{
		bShowInventory = !bShowInventory;
		
		hud->ToggleCraftMenu();
	}

}

void UCInventoryComponent::CheckLookAt()
{
	UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	CheckNull(camera);

	FVector start = camera->GetComponentTransform().GetLocation();
	FVector end = start + camera->GetComponentTransform().GetRotation().GetForwardVector() * 300;

	TArray<AActor*> ignores;
	ignores.Add(OwnerCharacter);

	FHitResult result;

	bool bHit = UKismetSystemLibrary::LineTraceSingle(OwnerCharacter->GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery17, false, ignores, EDrawDebugTrace::None, result, false);

	if (!bHit)
	{
		Target = nullptr;	

		return;
	}
	
	Target = Cast<ACItemBase>(result.GetActor());
	CheckNull(Target);

	Target->LookAt(OwnerCharacter);

}

bool UCInventoryComponent::AddToInventory(TSubclassOf<class ACItemBase> InItem, int32 Quantity)
{
	if (Inventory.Find(InItem))
		Inventory.Add(InItem, FMath::Clamp((*Inventory.Find(InItem) + Quantity), 0, 9999));
	else Inventory.Add(InItem, Quantity);

	return true;

}
 
FQueryResult UCInventoryComponent::QueryInventory(TSubclassOf<class ACItemBase> InItem, int32 Quantity)
{
	FQueryResult result;

	if (Quantity >= *Inventory.Find(InItem))
	{
		if (Inventory.Find(InItem) and Inventory[InItem] >= Quantity)
			result.bSuccess = true;
		else result.bSuccess = false;

		result.Quantity = *Inventory.Find(InItem);
	}

	return result;

}

bool UCInventoryComponent::RemoveFromInventory(TSubclassOf<class ACItemBase> InItem, int32 Quantity)
{
	FQueryResult result = QueryInventory(InItem, Quantity);

	if (result.bSuccess)
	{
		Inventory.Add(InItem, FMath::Clamp(Quantity - result.Quantity, 0, 9999));

		return true;
	}
	else return false;

}
