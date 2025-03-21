#include "PJS/Components/CBuildComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/StaticMesh.h"

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
	//InEnhancedInput->BindAction(IA_Select, ETriggerEvent::Triggered, this, &UCBuildComponent::Select);

}

void UCBuildComponent::Select(const FInputActionValue& InVal)
{

}

void UCBuildComponent::BuildMode()
{
	bOnBuildMode = !bOnBuildMode;

	if (bOnBuildMode)
		LoopBuild();
	else StopBuild();

}

void UCBuildComponent::LoopBuild()
{
	FVector location = OwnerCharacter->GetActorLocation();
	FVector forward = OwnerCharacter->GetActorForwardVector();

	FVector start = location + (forward * 350);
	FVector end = location + (forward * 1000);

	FHitResult result;

	FCollisionQueryParams params;
	params.AddIgnoredActor(OwnerCharacter);

	bHit = GetWorld()->LineTraceSingleByChannel(result, start, end, ECC_Visibility, params);
	if (bHit)
	{
		BuildTransform.SetLocation(result.ImpactPoint);

		if (Mesh)
			ChangeMeshOutLine(true);
		else SpawnMesh();

	}
	else
	{
		BuildTransform.SetLocation(result.TraceEnd);

		if (Mesh)
			ChangeMeshOutLine(false);
		else SpawnMesh();
	}

	Delay();

}

void UCBuildComponent::StopBuild()
{
	ResetBuild();

	GetWorld()->GetTimerManager().ClearTimer(BuildHandle);

}

void UCBuildComponent::Delay()
{
	if (bOnBuildMode)
	{
		auto lambda = [this]()
			{
				LoopBuild();
			};

		GetWorld()->GetTimerManager().SetTimer(BuildHandle, lambda, 0.01, true);

		//FLatentActionInfo info;
		//UKismetSystemLibrary::Delay(GetWorld(), 0.01, info);

	}
	else ResetBuild();

}

void UCBuildComponent::ResetBuild()
{
	bOnBuildMode = false;
	bCanBuild = false;

	if (Mesh)
	{
		if (UStaticMeshComponent* mesh = OwnerCharacter->GetComponentByClass<UStaticMeshComponent>())
			int a = 0;
	}

}

void UCBuildComponent::SpawnMesh()
{
	Mesh = Cast<UStaticMeshComponent>(OwnerCharacter->AddComponentByClass(UStaticMeshComponent::StaticClass(), false, BuildTransform, false));

	if (foundation)
	{
		Mesh->SetStaticMesh(foundation);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

void UCBuildComponent::ChangeMeshOutLine(bool bGreen)
{
	bCanBuild = false;

	foundation->SetMaterial(0, Materials[bGreen]);

	Mesh->SetWorldTransform(BuildTransform);

}
