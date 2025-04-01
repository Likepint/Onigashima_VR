#pragma once

#include "CoreMinimal.h"
#include "PJS/Crafts/CItemBase.h"
#include "CItem_Pick.generated.h"

UCLASS()
class ONIGASHIMA_API ACItem_Pick : public ACItemBase
{
	GENERATED_BODY()
	
public:
	ACItem_Pick();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
