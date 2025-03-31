#include "PJS/Widgets/CMenu.h"
#include "Global.h"
#include "Components/WidgetComponent.h"

ACMenu::ACMenu()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene", RootComponent);
	CHelpers::CreateComponent<UWidgetComponent>(this, &Widget, "Widget", Scene);

}

void ACMenu::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
