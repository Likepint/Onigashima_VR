#include "PJS/Components/CBuildComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "PJS/Builds/CBuildAsset.h"

UCBuildComponent::UCBuildComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CHelpers::GetAsset<UInputAction>(&IA_Build, "/Script/EnhancedInput.InputAction'/Game/PJS/Inputs/IA_Build_PJS.IA_Build_PJS'");
	CHelpers::GetAsset<UInputAction>(&IA_Select, "/Script/EnhancedInput.InputAction'/Game/PJS/Inputs/IA_Select_PJS.IA_Select_PJS'");

}

void UCBuildComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

}

void UCBuildComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCBuildComponent::OnBindEnhancedInputSystem(UEnhancedInputComponent* InEnhancedInput)
{
	InEnhancedInput->BindAction(IA_Build, ETriggerEvent::Started, this, &UCBuildComponent::BuildMode);
	InEnhancedInput->BindAction(IA_Select, ETriggerEvent::Triggered, this, &UCBuildComponent::Select);

}

void UCBuildComponent::Select(const FInputActionValue& InVal)
{
	if (InVal.Get<float>() > 0)
		++BuildIndex %= BuildAsset->GetMeshCnt();
	else BuildIndex - 1 < 0 ? BuildIndex = BuildAsset->GetMeshCnt() - 1 : --BuildIndex;

}

void UCBuildComponent::BuildMode()
{
	bOnBuildMode = !bOnBuildMode;

	if (bOnBuildMode)
		 LoopBuild();
	else StopBuild();

}

void UCBuildComponent::DelayBuild()
{
	if (bOnBuildMode)
	{
		auto lambda = [this]() { LoopBuild(); };

		GetWorld()->GetTimerManager().SetTimer(hBuild, lambda, 0.01, true);
	}
	else ResetBuild();

}

void UCBuildComponent::LoopBuild()
{
	FVector location = OwnerCharacter->GetActorLocation();
	FVector forward = OwnerCharacter->GetActorForwardVector();

	FVector start = location + (forward * 350);
	FVector end = location + (forward * 1000);

	TArray<AActor*> actors;
	FHitResult info;
	bool bHit = UKismetSystemLibrary::LineTraceSingle(OwnerCharacter->GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery1, false, actors, EDrawDebugTrace::None, info, true);

	if (bHit) BuildTransform.SetLocation(info.ImpactPoint);
	else BuildTransform.SetLocation(info.TraceEnd);

	if (Mesh) SetOutLine(bHit);
	else SpawnMesh();

	Mesh->SetStaticMesh(BuildAsset->GetStaticMesh(BuildIndex));

	DelayBuild();

}

void UCBuildComponent::StopBuild()
{
	ResetBuild();

	GetWorld()->GetTimerManager().ClearTimer(hBuild);

}

void UCBuildComponent::ResetBuild()
{
	bOnBuildMode = false;
	bCanBuild = false;

	if (Mesh)
	{
		Mesh->DestroyComponent();
		Mesh = nullptr;
	}
}

void UCBuildComponent::SpawnMesh()
{
	Mesh = Cast<UStaticMeshComponent>(OwnerCharacter->AddComponentByClass(UStaticMeshComponent::StaticClass(), false, BuildTransform, false));

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void UCBuildComponent::SetOutLine(bool bGreen)
{
	bCanBuild = false;

	for (int32 i = Mesh->GetMaterials().Num() - 1; i >= 0; --i)
		Mesh->SetMaterial(i, BuildAsset->GetMaterial(bGreen));

	Mesh->SetWorldTransform(BuildTransform);

}
