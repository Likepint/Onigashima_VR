#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJS/Builds/IBuild.h"
#include "CBuildMesh.generated.h"

UCLASS()
class ONIGASHIMA_API ACBuildMesh
	: public AActor
	, public IIBuild
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	TArray<class UBoxComponent*> SnapCollision;
	
public:
	ACBuildMesh();

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void OnDamageProcess(int32 InDamage) override;

public:
	TArray<class UBoxComponent*> ReturnBoxes() override;

protected:
	TArray<FVector> Coords;
	TArray<FRotator> Rotations;
	TArray<FVector> Extents;

private:
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 Health = 100;

};
