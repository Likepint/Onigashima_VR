#include "PJS/Builds/CBuildMesh.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "KJY/CEnemy.h"

ACBuildMesh::ACBuildMesh()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UStaticMeshComponent>(this, &StaticMesh, "StaticMesh");

}

void ACBuildMesh::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CheckNull(StaticMesh);
	CheckNull(StaticMesh->GetStaticMesh());

	// 현재의 스태틱메시의 Extent 로드
	FVector extent = StaticMesh->GetStaticMesh()->GetBounds().BoxExtent;

	CheckTrue(Coords.IsEmpty());

	for (int i = 0; i < Coords.Num(); ++i)
	{
		// Extent만큼 상대 위치 이동
		SnapCollision[i]->SetRelativeLocation(FVector(extent.X * Coords[i].X, extent.Y * Coords[i].Y, Coords[i].Z == 0 ? extent.Z : Coords[i].Z));

	}

}

void ACBuildMesh::BeginPlay()
{
	Super::BeginPlay();

}

void ACBuildMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBuildMesh::OnDamageProcess(int32 InDamage)
{
	Health -= InDamage;

	if (Health <= 0)
	{
		Destroy();

		return;
	}

}

TArray<class UBoxComponent*> ACBuildMesh::ReturnBoxes()
{
	return SnapCollision;

}
