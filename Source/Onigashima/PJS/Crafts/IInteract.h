#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteract.generated.h"

UINTERFACE(MinimalAPI)
class UIInteract : public UInterface
{
	GENERATED_BODY()

};

class ONIGASHIMA_API IIInteract
{
	GENERATED_BODY()

public:
	virtual void LookAt(class ACharacter* OwnerCharacter);

	virtual void InteractWith(class ACharacter* OwnerCharacter);

};
