#pragma once

#include "CoreMinimal.h"
#include "PJS/Builds/CBuildMesh.h"
#include "CBuildMesh_Floor.generated.h"

UCLASS()
class ONIGASHIMA_API ACBuildMesh_Floor : public ACBuildMesh
{
	GENERATED_BODY()

public:
	ACBuildMesh_Floor();

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
