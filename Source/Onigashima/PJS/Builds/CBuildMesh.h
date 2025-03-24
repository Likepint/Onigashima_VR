#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJS/Builds/IBuild.h"
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
class ONIGASHIMA_API ACBuildMesh
	: public AActor
	, public IIBuild
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

	UPROPERTY(EditAnywhere)
	TArray<class UBoxComponent*> BoxComponents;
	
public:
	ACBuildMesh();

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	TArray<class UBoxComponent*> ReturnBoxes() override;

private:
	// 스태틱 메시 기준으로 위에서 아래를 보는 기준
	// 오른쪽, 아래쪽, 왼쪽, 위쪽
	TArray<FAxisVal> Axis = { {2, 0}, {0, 2}, {-2, 0}, {0, -2} };

};
