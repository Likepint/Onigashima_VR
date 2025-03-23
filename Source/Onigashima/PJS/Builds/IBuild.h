#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBuild.generated.h"

UINTERFACE(MinimalAPI)
class UIBuild : public UInterface
{
	GENERATED_BODY()

};

class ONIGASHIMA_API IIBuild
{
	GENERATED_BODY()

public:
	virtual TArray<class UBoxComponent*> ReturnBoxes();

};
