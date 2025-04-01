#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CGameMode.generated.h"

UCLASS()
class ONIGASHIMA_API ACGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACGameMode();

public:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Sound")
    void ChangeBackgroundMusic(USoundBase* NewSound);

public:
	UPROPERTY()
	class USoundBase* GameSound;

	UPROPERTY()
    USoundBase* CombatSound;

	UPROPERTY()
    class UAudioComponent* CurrentAudioComponent;

};
