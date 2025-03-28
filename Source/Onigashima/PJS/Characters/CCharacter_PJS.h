#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacter_PJS.generated.h"

UCLASS()
class ONIGASHIMA_API ACCharacter_PJS : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

private:
	UPROPERTY(VisibleAnywhere)
	class UCTestMoveComponent* Movement;

	UPROPERTY(VisibleAnywhere)
	class UCBuildComponent* Build;
	
	UPROPERTY(VisibleAnywhere)
	class UCInventoryComponent* Inventory;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced")
	class UInputMappingContext* MappingContext;

public:
	ACCharacter_PJS();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
