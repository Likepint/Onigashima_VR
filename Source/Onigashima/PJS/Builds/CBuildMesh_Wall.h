#pragma once

#include "CoreMinimal.h"
#include "PJS/Builds/CBuildMesh.h"
#include "CBuildMesh_Wall.generated.h"

UCLASS()
class ONIGASHIMA_API ACBuildMesh_Wall : public ACBuildMesh
{
	GENERATED_BODY()
	
public:
	ACBuildMesh_Wall();

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
