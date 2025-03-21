#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CollisionQueryParams.h"
#include "CBuildAsset.generated.h"

USTRUCT()
struct FBuildStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ETraceTypeQuery> TraceChannel;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACBuildMesh> Ref;

};

UCLASS()
class ONIGASHIMA_API UCBuildAsset : public UDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	TArray<class UMaterialInstance*> Materials;

	UPROPERTY(EditAnywhere)
	TArray<FBuildStruct> BuildStruct;

public:
	UMaterialInstance* GetMaterial(bool bGreen);
	const FBuildStruct& GetStruct(int32 InIndex);

	int32 GetMeshCnt();

};
