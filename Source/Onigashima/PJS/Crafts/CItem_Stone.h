#pragma once

#include "CoreMinimal.h"
#include "PJS/Crafts/CItemBase.h"
#include "CItem_Stone.generated.h"

UCLASS()
class ONIGASHIMA_API ACItem_Stone : public ACItemBase
{
	GENERATED_BODY()

public:
	ACItem_Stone();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
