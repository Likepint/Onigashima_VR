#include "PJS/Characters/CPlayerController.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "PJS/Components/CInventoryComponent.h"

ACPlayerController::ACPlayerController()
{

}

void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	HUD = CHelpers::GetComponent<UCInventoryComponent>(OwnerCharacter)->GetHUD();

}
