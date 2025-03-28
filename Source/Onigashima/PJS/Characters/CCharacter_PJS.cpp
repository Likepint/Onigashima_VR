#include "PJS/Characters/CCharacter_PJS.h"
#include "Global.h"
#include "Camera/CameraComponent.h"
#include "PJS/Components/CTestMoveComponent.h"
#include "PJS/Components/CBuildComponent.h"
#include "PJS/Components/CInventoryComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ACCharacter_PJS::ACCharacter_PJS()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = true;

	GetCapsuleComponent()->SetHiddenInGame(false);

	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", RootComponent);

	CHelpers::CreateActorComponent<UCTestMoveComponent>(this, &Movement, "Movement");

	CHelpers::CreateActorComponent<UCBuildComponent>(this, &Build, "Build");

	CHelpers::CreateActorComponent<UCInventoryComponent>(this, &Inventory, "Inventory");

	CHelpers::GetAsset<UInputMappingContext>(&MappingContext, "/Script/EnhancedInput.InputMappingContext'/Game/PJS/Inputs/IMC_Context_PJS.IMC_Context_PJS'");

}

void ACCharacter_PJS::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* controller = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer()))
			subsystem->AddMappingContext(MappingContext, 0);
	}

}

void ACCharacter_PJS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCharacter_PJS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Movement->OnBindEnhancedInputSystem(EnhancedInput);

		Build->OnBindEnhancedInputSystem(EnhancedInput);

		Inventory->OnBindEnhancedInputSystem(EnhancedInput);

	}

}
