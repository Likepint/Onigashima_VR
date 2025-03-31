#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJS/Crafts/IInteract.h"
#include "CItemBase.generated.h"

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Parts = 0, Ammo, MAX
};

USTRUCT()
struct FItemStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName Name;

	UPROPERTY(EditAnywhere)
	FName Description;

	UPROPERTY(EditAnywhere)
	EItemCategory category = EItemCategory::MAX;

	UPROPERTY(EditAnywhere)
	bool bCraftable = false;

	UPROPERTY(EditAnywhere)
	class UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<class ACItemBase>, int32> Recipe;

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

public:
	const FItemStruct& GetItemStruct() { return ItemStruct; };

protected:
	UPROPERTY(EditAnywhere)
	FItemStruct ItemStruct;

};
