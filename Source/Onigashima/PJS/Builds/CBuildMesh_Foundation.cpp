#include "PJS/Builds/CBuildMesh_Foundation.h"
#include "Global.h"
#include "Components/BoxComponent.h"

ACBuildMesh_Foundation::ACBuildMesh_Foundation()
{
	PrimaryActorTick.bCanEverTick = true;

	for (int32 i = 1; i <= 4; ++i)
	{
		FString name = FString::Printf(TEXT("Foundation%d"), i);
		// 이름을 Foundation 1 ~ 4로 설정
		UBoxComponent* box = CreateDefaultSubobject<UBoxComponent>(*name);
		// BoxComponent를 위에서 설정한 이름으로 지정하여 생성

		box->SetupAttachment(StaticMesh);

		// BoxComponents 배열에 추가
		SnapCollision.Add(box);
	} // Foundation

	for (int32 i = 1; i <= 4; ++i)
	{
		FString name = FString::Printf(TEXT("Wall%d"), i);
		// 이름을 Wall 1 ~ 4로 설정
		UBoxComponent* box = CreateDefaultSubobject<UBoxComponent>(*name);
		// BoxComponent를 위에서 설정한 이름으로 지정하여 생성

		box->SetupAttachment(StaticMesh);

		// BoxComponents 배열에 추가
		SnapCollision.Add(box);
	} // Wall

	Coords = { {2, 0, 0}, {0, 2, 0}, {-2, 0, 0}, {0, -2, 0}, {1, 0, 300}, {0, 1, 300}, {-1, 0, 300}, {0, -1, 300} };

}

void ACBuildMesh_Foundation::PostInitializeComponents()
{
	CheckNull(StaticMesh);
	CheckNull(StaticMesh->GetStaticMesh());

	Super::PostInitializeComponents();

	// 박스 크기를 스태틱메시의 Extent와 동일하게 설정
	// SnapCollision[i]->SetBoxExtent(extent);

	FVector extent = StaticMesh->GetStaticMesh()->GetBounds().BoxExtent;

	for (int32 i = 0; i < 4; ++i)
	{
		Extents.Add(extent);

		Rotations.Add({ 0, 0, 0 });
	}

	for (int32 i = 0; i < 4; ++i)
		Extents.Add({ 200, 32, 200 });

	Rotations.Add({ 0, -90, 0 });
	Rotations.Add({ 0, 0, 0 });
	Rotations.Add({ 0, 90, 0 });
	Rotations.Add({ 0, 0, 0 });

	CheckTrue(Rotations.IsEmpty());
	CheckTrue(Extents.IsEmpty());

	for (int32 i = 0; i < Rotations.Num(); ++i)
	{
		SnapCollision[i]->SetRelativeRotation(FQuat(Rotations[i]));
		SnapCollision[i]->SetBoxExtent(Extents[i]);
	}

}

void ACBuildMesh_Foundation::BeginPlay()
{
	Super::BeginPlay();

}

void ACBuildMesh_Foundation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
