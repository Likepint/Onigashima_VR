#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJS/Crafts/IInteract.h"
#include "CItemBase.generated.h"

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Parts = 0, Ammo, Turret, MAX
};

UCLASS()
class ONIGASHIMA_API ACItemBase
	: public AActor
	, public IIInteract
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;
	
public:	
	ACItemBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void LookAt(class ACharacter* OwnerCharacter) override;

	virtual void InteractWith(class ACharacter* OwnerCharacter) override;

protected:
	UPROPERTY(VisibleAnywhere)
	FName Name;

	UPROPERTY(VisibleAnywhere)
	FName Description;

	UPROPERTY(VisibleAnywhere)
	EItemCategory category = EItemCategory::MAX;

	UPROPERTY(VisibleAnywhere)
	bool bCraftable = false;

	UPROPERTY(VisibleAnywhere)
	class UTexture2D* Thumbnail;

};
