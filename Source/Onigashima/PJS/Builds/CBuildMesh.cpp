#include "PJS/Builds/CBuildMesh.h"
#include "Global.h"
#include "Components/BoxComponent.h"

ACBuildMesh::ACBuildMesh()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UStaticMeshComponent>(this, &StaticMesh, "StaticMesh");

	//CHelpers::CreateComponent<UBoxComponent>(this, &Box1, "Box1", StaticMesh);
	//CHelpers::CreateComponent<UBoxComponent>(this, &Box2, "Box2", StaticMesh);
	//CHelpers::CreateComponent<UBoxComponent>(this, &Box3, "Box3", StaticMesh);
	//CHelpers::CreateComponent<UBoxComponent>(this, &Box4, "Box4", StaticMesh);

	for (int32 i = 0; i < 4; ++i)
	{
		FString name = FString::Printf(TEXT("Box%d"), i + 1);
		// �̸��� Box 1 ~ 4�� ����
		UBoxComponent* box = CreateDefaultSubobject<UBoxComponent>(*name);
		// BoxComponent�� ������ ������ �̸����� �����Ͽ� ����

		box->SetupAttachment(StaticMesh);

		// BoxComponents �迭�� �߰�
		BoxComponents.Add(box);
	}

}

void ACBuildMesh::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CheckNull(StaticMesh);

	// ������ ����ƽ�޽��� Extent �ε�
	FVector extent = StaticMesh->GetStaticMesh()->GetBounds().BoxExtent;

	//Box1->SetRelativeLocation(FVector(extent.X * 2, 0, extent.Z));
	//Box1->SetBoxExtent(FVector(extent));

	//Box2->SetRelativeLocation(FVector(0, extent.Y * 2, extent.Z));
	//Box2->SetBoxExtent(FVector(extent));

	//Box3->SetRelativeLocation(FVector(-extent.X * 2, 0, extent.Z));
	//Box3->SetBoxExtent(FVector(extent));

	//Box4->SetRelativeLocation(FVector(0, -extent.Y * 2, extent.Z));
	//Box4->SetBoxExtent(FVector(extent));

	for (int i = 0; i < Axis.Num(); ++i)
	{
		// Extent��ŭ ��� ��ġ �̵�
		BoxComponents[i]->SetRelativeLocation(FVector(extent.X * Axis[i].x, extent.Y * Axis[i].y, extent.Z));
		// �ڽ� ũ�⸦ ����ƽ�޽��� Extent�� �����ϰ� ����
		BoxComponents[i]->SetBoxExtent(extent);

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

TArray<class UBoxComponent*> ACBuildMesh::ReturnBoxes()
{
	return BoxComponents;

}
