#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

UCLASS()
class ONIGASHIMA_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACPlayerController();

protected:
	virtual void BeginPlay() override;

private:
	class ACharacter* OwnerCharacter;

	class UUserWidget* HUD;

};
