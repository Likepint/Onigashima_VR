#include "PJS/Builds/CBuildAsset.h"
#include "Global.h"

UMaterialInstance* UCBuildAsset::GetMaterial(bool bGreen)
{
	return Materials[bGreen];

}

const FBuildStruct& UCBuildAsset::GetStruct(int32 InIndex)
{
	return BuildStruct[InIndex];

}

int32 UCBuildAsset::GetMeshCnt()
{
	return BuildStruct.Num();

}
