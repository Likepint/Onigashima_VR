﻿#pragma once

#include "CoreMinimal.h"
#include "PJS/Components/CBaseComponent.h"
#include "CInventoryComponent.generated.h"

USTRUCT()
struct FQueryResult
{
	GENERATED_BODY()

public:
	bool bSuccess = false;

	int32 Quantity;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONIGASHIMA_API UCInventoryComponent : public UCBaseComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> UI_HUD;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced")
	class UInputAction* IA_Interact;

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced")
	class UInputAction* IA_Craft;

public:	
	UCInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void OnBindEnhancedInputSystem(class UEnhancedInputComponent* InEnhancedInput) override;

private:
	void OnInteract(const struct FInputActionValue& InVal);
	void OnInteractUI(const struct FInputActionValue& InVal);
	void OnCraft(const struct FInputActionValue& InVal);

public:
	UUserWidget* GetHUD() { return HUD; }

	TMap<TSubclassOf<class ACItemBase>, int32>& GetInventory() { return Inventory; };

private:
	void CheckLookAt();

public:
	bool AddToInventory(TSubclassOf<class ACItemBase> InItem, int32 Quantity);
	FQueryResult QueryInventory(TSubclassOf<class ACItemBase> InItem, int32 Quantity);
	bool RemoveFromInventory(TSubclassOf<class ACItemBase> InItem, int32 Quantity);

private:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TMap<TSubclassOf<class ACItemBase>, int32> Inventory;

private:
	class ACItemBase* Target;

	class UUserWidget* HUD;

private:
	bool bShowInventory = false;

};
