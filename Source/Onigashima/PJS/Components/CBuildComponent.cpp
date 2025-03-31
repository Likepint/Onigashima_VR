#include "PJS/Components/CBuildComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "PJS/Builds/CBuildAsset.h"
#include "PJS/Builds/CBuildMesh.h"
#include "Components/BoxComponent.h"

UCBuildComponent::UCBuildComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CHelpers::GetAsset<UInputAction>(&IA_OnBuild, "/Script/EnhancedInput.InputAction'/Game/PJS/Inputs/IA_OnBuild_PJS.IA_OnBuild_PJS'");
	CHelpers::GetAsset<UInputAction>(&IA_Select, "/Script/EnhancedInput.InputAction'/Game/PJS/Inputs/IA_Select_PJS.IA_Select_PJS'");
	CHelpers::GetAsset<UInputAction>(&IA_Build, "/Script/EnhancedInput.InputAction'/Game/PJS/Inputs/IA_Build_PJS.IA_Build_PJS'");
	CHelpers::GetAsset<UInputAction>(&IA_Rotate, "/Script/EnhancedInput.InputAction'/Game/PJS/Inputs/IA_Rotate_PJS.IA_Rotate_PJS'");

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
	InEnhancedInput->BindAction(IA_OnBuild, ETriggerEvent::Started, this, &UCBuildComponent::BuildMode);
	InEnhancedInput->BindAction(IA_Select, ETriggerEvent::Triggered, this, &UCBuildComponent::SelectOrRotate);
	InEnhancedInput->BindAction(IA_Build, ETriggerEvent::Started, this, &UCBuildComponent::SpawnBuild);
	InEnhancedInput->BindAction(IA_Rotate, ETriggerEvent::Started, this, &UCBuildComponent::Rotate);
	InEnhancedInput->BindAction(IA_Rotate, ETriggerEvent::Completed, this, &UCBuildComponent::Rotate);

}

void UCBuildComponent::BuildMode(const struct FInputActionValue& InVal)
{
	bOnBuildMode = !bOnBuildMode;

	if (bOnBuildMode)
		LoopBuild();
	else StopBuild();

}

void UCBuildComponent::SelectOrRotate(const FInputActionValue& InVal)
{
	if (!bOnBuildMode) return;

	if (bRotate)
	{
		//FRotator rot = Mesh->GetComponentRotation() + FRotator(0, InVal.Get<float>(), 0);

		//BuildTransform.SetRotation(FQuat(rot));

		Mesh->AddWorldRotation(FQuat(FRotator(0, InVal.Get<float>() * 5, 0)));

		BuildTransform.SetRotation(Mesh->GetComponentQuat());

		return;
	}
	else
	{
		if (InVal.Get<float>() > 0)
			++BuildID %= BuildAsset->GetMeshCnt();
		else BuildID - 1 < 0 ? BuildID = BuildAsset->GetMeshCnt() - 1 : --BuildID;
	}

	ChangeMesh();

}

void UCBuildComponent::Rotate(const FInputActionValue& InVal)
{
	bRotate = !bRotate;

}

void UCBuildComponent::SpawnBuild(const struct FInputActionValue& InVal)
{
	CheckFalse(bOnBuildMode);
	CheckFalse(bCanBuild);

	FActorSpawnParameters params;

	OwnerCharacter->GetWorld()->SpawnActor<ACBuildMesh>(BuildAsset->GetStruct(BuildID).Ref, BuildTransform, params);

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
	UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	CheckNull(camera);

	FVector location = camera->GetComponentLocation();
	FVector forward = camera->GetForwardVector();

	FVector start = location + (forward * 350);
	FVector end = location + (forward * 1000);

	TArray<AActor*> actors;
	FHitResult info;
	bool bHit = UKismetSystemLibrary::LineTraceSingle(OwnerCharacter->GetWorld(), start, end, BuildAsset->GetStruct(BuildID).TraceChannel, false, actors, EDrawDebugTrace::None, info, true);

	bHit ? BuildTransform.SetLocation(info.ImpactPoint) : BuildTransform.SetLocation(info.TraceEnd);

	//if (bHit) BuildTransform.SetLocation(info.ImpactPoint);
	//else BuildTransform.SetLocation(info.TraceEnd);

	//if (Mesh) SetOutLine(bHit);
	//else SpawnMesh();

	//Mesh ? SetOutLine(bHit) : SpawnMesh();

	if (Mesh)
	{
		FDetectBuild detected = GetDetectBuild(info.GetActor(), info.GetComponent());

		if (detected.bFound)
		{
			BuildTransform = detected.Transform;
			BuildTransform.SetLocation(BuildTransform.GetLocation() - FVector(0, 0, Mesh->GetStaticMesh()->GetBounds().BoxExtent.Z));
		}

		SetOutLine(bHit);
	}
	else SpawnMesh();

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

	Mesh->SetStaticMesh(BuildAsset->GetStruct(BuildID).StaticMesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void UCBuildComponent::SetOutLine(bool bGreen)
{
	bCanBuild = bGreen;

	for (int32 i = Mesh->GetMaterials().Num() - 1; i >= 0; --i)
		Mesh->SetMaterial(i, BuildAsset->GetMaterial(bGreen));

	Mesh->SetWorldTransform(BuildTransform);

}

void UCBuildComponent::ChangeMesh()
{
	if (Mesh)
		Mesh->SetStaticMesh(BuildAsset->GetStruct(BuildID).StaticMesh);

}

FDetectBuild UCBuildComponent::GetDetectBuild(class AActor* InHitActor, class UPrimitiveComponent* InHitComponent)
{
	ACBuildMesh* mesh = Cast<ACBuildMesh>(InHitActor);
	CheckNullResult(mesh, FDetectBuild());

	TArray<UBoxComponent*> boxes = mesh->ReturnBoxes();

	bool bLocalFound = false;

	for (const auto& box : boxes)
	{
		if (box != InHitComponent) continue;

		bLocalFound = true;

		break;
	}
	
	return FDetectBuild(bLocalFound, InHitComponent->GetComponentTransform());

}
