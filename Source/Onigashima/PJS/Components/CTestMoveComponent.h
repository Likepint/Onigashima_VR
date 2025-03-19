#pragma once

#include "CoreMinimal.h"
#include "PJS/Components/CBaseComponent.h"
#include "CTestMoveComponent.generated.h"

UCLASS()
class ONIGASHIMA_API UCTestMoveComponent : public UCBaseComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputAction* IA_Movement;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputAction* IA_Look;
	
public:
	UCTestMoveComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnBindEnhancedInputSystem(class UEnhancedInputComponent* InEnhancedInput) override;

private:
	void OnMovement(const struct FInputActionValue& InVal);

	void OnLook(const struct FInputActionValue& InVal);

};
