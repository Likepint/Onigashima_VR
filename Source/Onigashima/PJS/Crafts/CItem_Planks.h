#pragma once

#include "CoreMinimal.h"
#include "PJS/Crafts/CItemBase.h"
#include "CItem_Planks.generated.h"

UCLASS()
class ONIGASHIMA_API ACItem_Planks : public ACItemBase
{
	GENERATED_BODY()
	
public:
	ACItem_Planks();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
