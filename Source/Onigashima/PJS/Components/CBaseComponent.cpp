#include "PJS/Components/CBaseComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

UCBaseComponent::UCBaseComponent()
{
	bWantsInitializeComponent = true;

	PrimaryComponentTick.bCanEverTick = true;

}

void UCBaseComponent::InitializeComponent()
{
	Super::InitializeComponent();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);

}

void UCBaseComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
