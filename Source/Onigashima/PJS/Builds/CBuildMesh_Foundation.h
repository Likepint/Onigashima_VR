#pragma once

#include "CoreMinimal.h"
#include "PJS/Builds/CBuildMesh.h"
#include "CBuildMesh_Foundation.generated.h"

UCLASS()
class ONIGASHIMA_API ACBuildMesh_Foundation : public ACBuildMesh
{
	GENERATED_BODY()

public:
	ACBuildMesh_Foundation();

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
