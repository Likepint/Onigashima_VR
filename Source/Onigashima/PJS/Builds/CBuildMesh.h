#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBuildMesh.generated.h"

USTRUCT()
struct FAxisVal
{
	GENERATED_BODY()

public:
	int x = 0;
	int y = 0;

};

UCLASS()
class ONIGASHIMA_API ACBuildMesh : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;

	//UPROPERTY(VisibleAnywhere)
	//class UBoxComponent* Box1;

	//UPROPERTY(VisibleAnywhere)
	//class UBoxComponent* Box2;

	//UPROPERTY(VisibleAnywhere)
	//class UBoxComponent* Box3;

	//UPROPERTY(VisibleAnywhere)
	//class UBoxComponent* Box4;

	UPROPERTY(VisibleAnywhere)
	TArray<class UBoxComponent*> BoxComponents;
	
public:
	ACBuildMesh();

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	TArray<FAxisVal> Axis = { {2, 0}, {0, 2}, {-2, 0}, {0, -2} };

};
