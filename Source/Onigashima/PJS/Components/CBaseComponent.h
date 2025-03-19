#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONIGASHIMA_API UCBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCBaseComponent();

	virtual void InitializeComponent() override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void OnBindEnhancedInputSystem(class UEnhancedInputComponent* InEnhancedInput) {};

protected:
	class ACharacter* OwnerCharacter;

};
