#pragma once

#include "CoreMinimal.h"
#include "PJS/Crafts/CItemBase.h"
#include "CItem_Axe.generated.h"

UCLASS()
class ONIGASHIMA_API ACItem_Axe : public ACItemBase
{
	GENERATED_BODY()

public:
	ACItem_Axe();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
