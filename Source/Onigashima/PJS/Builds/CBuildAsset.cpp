#include "PJS/Builds/CBuildAsset.h"
#include "Global.h"

UMaterialInstance* UCBuildAsset::GetMaterial(bool bGreen)
{
	return Materials[bGreen];

}

UStaticMesh* UCBuildAsset::GetStaticMesh(int32 InIndex)
{
	return BuildMesh[InIndex];

}

int32 UCBuildAsset::GetMeshCnt()
{
	return BuildMesh.Num();

}
