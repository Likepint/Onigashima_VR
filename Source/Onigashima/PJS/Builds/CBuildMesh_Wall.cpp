#include "PJS/Builds/CBuildMesh_Wall.h"
#include "Global.h"
#include "Components/BoxComponent.h"

ACBuildMesh_Wall::ACBuildMesh_Wall()
{
	PrimaryActorTick.bCanEverTick = true;

	for (int32 i = 1; i <= 2; ++i)
	{
		FString name = FString::Printf(TEXT("Wall%d"), i);
		// 이름을 Foundation 1 ~ 4로 설정
		UBoxComponent* box = CreateDefaultSubobject<UBoxComponent>(*name);
		// BoxComponent를 위에서 설정한 이름으로 지정하여 생성

		box->SetupAttachment(StaticMesh);

		// BoxComponents 배열에 추가
		SnapCollision.Add(box);
	} // Foundation

	Coords = { { 2, 0, 0 }, { -2, 0, 0 } };

}

void ACBuildMesh_Wall::PostInitializeComponents()
{
	CheckNull(StaticMesh);
	CheckNull(StaticMesh->GetStaticMesh());

	Super::PostInitializeComponents();

	FVector extent = StaticMesh->GetStaticMesh()->GetBounds().BoxExtent;

	for (int32 i = 0; i < 2; ++i)
	{
		Extents.Add(extent);

		Rotations.Add({ 0, 0, 0 });
	}

	CheckTrue(Rotations.IsEmpty());
	CheckTrue(Extents.IsEmpty());

	for (int32 i = 0; i < Rotations.Num(); ++i)
	{
		SnapCollision[i]->SetRelativeRotation(FQuat(Rotations[i]));
		SnapCollision[i]->SetBoxExtent(Extents[i]);
	}
}

void ACBuildMesh_Wall::BeginPlay()
{
	Super::BeginPlay();

}

void ACBuildMesh_Wall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
