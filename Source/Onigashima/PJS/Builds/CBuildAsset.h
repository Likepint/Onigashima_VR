#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CBuildAsset.generated.h"

UCLASS()
class ONIGASHIMA_API UCBuildAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<class UMaterialInstance*> Materials;

	UPROPERTY(EditAnywhere)
	TArray<class UStaticMesh*> BuildMesh;

public:
	UMaterialInstance* GetMaterial(bool bGreen);
	UStaticMesh* GetStaticMesh(int32 InIndex);

	int32 GetMeshCnt();

};
