#pragma once

#include "CoreMinimal.h"
#include "PJS/Crafts/CItemBase.h"
#include "CItem_Bow.generated.h"

UCLASS()
class ONIGASHIMA_API ACItem_Bow : public ACItemBase
{
	GENERATED_BODY()
	
public:
	ACItem_Bow();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
