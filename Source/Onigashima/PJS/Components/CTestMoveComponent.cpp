#include "PJS/Components/CTestMoveComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"

UCTestMoveComponent::UCTestMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CHelpers::GetAsset<UInputAction>(&IA_Movement, "/Script/EnhancedInput.InputAction'/Game/PJS/Inputs/IA_Movement_PJS.IA_Movement_PJS'");
	CHelpers::GetAsset<UInputAction>(&IA_Look, "/Script/EnhancedInput.InputAction'/Game/PJS/Inputs/IA_Look_PJS.IA_Look_PJS'");

}

void UCTestMoveComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCTestMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCTestMoveComponent::OnBindEnhancedInputSystem(UEnhancedInputComponent* InEnhancedInput)
{
	InEnhancedInput->BindAction(IA_Movement, ETriggerEvent::Triggered, this, &UCTestMoveComponent::OnMovement);

	InEnhancedInput->BindAction(IA_Look, ETriggerEvent::Triggered, this, &UCTestMoveComponent::OnLook);

}

void UCTestMoveComponent::OnMovement(const FInputActionValue& InVal)
{
	UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	CheckNull(camera);

	// Forward
	OwnerCharacter->AddMovementInput(camera->GetForwardVector(), InVal.Get<FVector2D>().X);

	// Right
	OwnerCharacter->AddMovementInput(camera->GetRightVector(), InVal.Get<FVector2D>().Y);

}

void UCTestMoveComponent::OnLook(const FInputActionValue& InVal)
{
	// Horizontal
	OwnerCharacter->AddControllerYawInput(InVal.Get<FVector2D>().X);

	// Vertical
	OwnerCharacter->AddControllerPitchInput(InVal.Get<FVector2D>().Y);

}
