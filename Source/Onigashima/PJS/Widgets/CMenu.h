#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMenu.generated.h"

UCLASS()
class ONIGASHIMA_API ACMenu : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* Widget;
	
public:	
	ACMenu();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
