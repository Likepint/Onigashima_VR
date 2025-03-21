// Fill out your copyright notice in the Description page of Project Settings.


#include "ODH/VRPlayer.h"
#include "Global.h"
#include "Camera/CameraComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "CVRPlayerAnim.h"
#include "Components/StaticMeshComponent.h"
#include "MotionControllerComponent.h"

// Sets default values
AVRPlayer::AVRPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //Camera Create
    VRCam = CreateDefaultSubobject<UCameraComponent>(L"VRCam");
    VRCam->SetupAttachment(RootComponent);
    //VRCam->SetRelativeLocation(FVector(0, 0, 70));
    VRCam->bUsePawnControlRotation = true;

    //Input Setting
    ConstructorHelpers::FObjectFinder<UInputMappingContext> Temp_IMC(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/ODH/Input/IMC_PlayerINput.IMC_PlayerInput'"));
    if (Temp_IMC.Succeeded())
    {
        IMC_VRInput = Temp_IMC.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> Temp_Move(TEXT("/Script/EnhancedInput.InputAction'/Game/ODH/Input/IA_PlayerMove.IA_PlayerMove'"));
    if (Temp_Move.Succeeded())
    {
        IA_Move = Temp_Move.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> Temp_Turn(L"/Script/EnhancedInput.InputAction'/Game/ODH/Input/IA_Turn.IA_Turn'");
    if (Temp_Turn.Succeeded())
    {
        IA_Turn = Temp_Turn.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> Temp_LeftGrap(L"/Script/EnhancedInput.InputAction'/Game/ODH/Input/IA_Left_Grap.IA_Left_Grap'");
    if (Temp_LeftGrap.Succeeded())
    {
        IA_LeftGrap = Temp_LeftGrap.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> Temp_LeftIndexCurl(L"/Script/EnhancedInput.InputAction'/Game/ODH/Input/IA_Left_IdexCurl.IA_Left_IdexCurl'");
    if (Temp_LeftIndexCurl.Succeeded())
    {
        IA_LeftIdexCurl = Temp_LeftIndexCurl.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> Temp_RightGrap(L"/Script/EnhancedInput.InputAction'/Game/ODH/Input/IA_Right_Grap.IA_Right_Grap'");
    if (Temp_RightGrap.Succeeded())
    {
        IA_RightGrap = Temp_RightGrap.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> Temp_RightIndexCurl(L"/Script/EnhancedInput.InputAction'/Game/ODH/Input/IA_Right_IdexCurl.IA_Right_IdexCurl'");
    if (Temp_RightIndexCurl.Succeeded())
    {
        IA_RightIdexCurl = Temp_RightIndexCurl.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> Temp_ItemMenu(L"/Script/EnhancedInput.InputAction'/Game/ODH/Input/IA_ItemMenu.IA_ItemMenu'");
    if (Temp_ItemMenu.Succeeded())
    {
        IA_ItemMenu = Temp_ItemMenu.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> Temp_ItemInter(L"/Script/EnhancedInput.InputAction'/Game/ODH/Input/IA_ItemInteraction.IA_ItemInteraction'");
    if (Temp_ItemInter.Succeeded())
    {
        IA_ItemInteraction = Temp_ItemInter.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> Temp_ItemTogle(L"/Script/EnhancedInput.InputAction'/Game/ODH/Input/IA_ItemTogle.IA_ItemTogle'");
    if (Temp_ItemTogle.Succeeded())
    {
        IA_ItemTogle = Temp_ItemTogle.Object;
    }

    // LeftHand Create
    LeftSceneComp = CreateDefaultSubobject<UMotionControllerComponent>(L"ControllerLftGrip");
    LeftSceneComp->SetupAttachment(RootComponent);
    
    LeftHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(L"LeftHand");
    LeftHandMesh->SetupAttachment(LeftSceneComp);

    ConstructorHelpers::FObjectFinder<USkeletalMesh> Temp_LeftHand(L"/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'");
    if (Temp_LeftHand.Succeeded())
    {
        LeftHandMesh->SetSkeletalMesh(Temp_LeftHand.Object);
        LeftHandMesh->SetRelativeRotation(FRotator(0, -90, 0));
    }

    // Right Hand Create
    RightSceneComp = CreateDefaultSubobject<UMotionControllerComponent>(L"ControllerRightGrip");
    RightSceneComp->SetupAttachment(RootComponent);

    RightHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(L"RightHand");
    RightHandMesh->SetupAttachment(RightSceneComp);

    ConstructorHelpers::FObjectFinder<USkeletalMesh> Temp_RightHand(L"/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'");
    if (Temp_RightHand.Succeeded())
    {
        RightHandMesh->SetSkeletalMesh(Temp_RightHand.Object);
        RightHandMesh->SetRelativeRotation(FRotator(0, -90, 0));
    }

    //Widget
//     ConstructorHelpers::FObjectFinder<UWidget> Temp_ItemWidget(L"/Script/UMGEditor.WidgetBlueprint'/Game/ODH/Widget/WBP_ItemMenu.WBP_ItemMenu'");
//     if (Temp_ItemWidget.Succeeded())
//     {
//         ItemMenuWidget = Temp_ItemWidget.Object;
//     }

    //equipment
    Spear = CreateDefaultSubobject<UStaticMeshComponent>(L"SpearComp");
    Spear->SetupAttachment(RightHandMesh, L"hand_rSocket");
    Spear->SetRelativeScale3D(FVector(0.2f));

    PickItem = CreateDefaultSubobject<UStaticMeshComponent>(L"PickComp");
    PickItem->SetupAttachment(RightHandMesh, L"hand_rSocket");
    PickItem->SetRelativeScale3D(FVector(0.2f));

    Axe = CreateDefaultSubobject<UStaticMeshComponent>(L"AxeComp");
    Axe->SetupAttachment(RightHandMesh, L"hand_rSocket");
    Axe->SetRelativeScale3D(FVector(0.2f));

    Bow = CreateDefaultSubobject<UStaticMeshComponent>(L"BowComp");
    Bow->SetupAttachment(RightHandMesh, L"hand_rSocket");
    Bow->SetRelativeScale3D(FVector(0.2f));
}

// Called when the game starts or when spawned
void AVRPlayer::BeginPlay()
{
	Super::BeginPlay();
	
    auto pc = GetWorld()->GetFirstPlayerController();
    if (pc)
    {
        auto player = pc->GetLocalPlayer();
        auto SS = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player);

        if (SS)
        {
            SS->AddMappingContext(IMC_VRInput, 1);
        }
    }

    Spear->SetVisibility(false);
    PickItem->SetVisibility(false);
    Axe->SetVisibility(false);
    Bow->SetVisibility(false);

    mItemState = EItemState::NoItem;

    LeftHandAnim = Cast<UCVRPlayerAnim>(LeftHandMesh->GetAnimInstance());
    RightHandAnim = Cast<UCVRPlayerAnim>(RightHandMesh->GetAnimInstance());

    TestItemPush();
}

// Called every frame
void AVRPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    switch (mItemState)
    {
    case EItemState::NoItem:
    	break;
    case EItemState::SetSpear:
        break;
    case EItemState::SetPick:
        break;
    case EItemState::SetAxe:
        break;
    case EItemState::SetBow:
        break;
    }
}

// Called to bind functionality to input
void AVRPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    auto InputSystem = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    if (InputSystem)
    {
        //Moving
        InputSystem->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AVRPlayer::Move);
        InputSystem->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &AVRPlayer::Turn);

        // Idle -> Graps Animation
        InputSystem->BindAction(IA_LeftGrap, ETriggerEvent::Triggered, this, &AVRPlayer::LeftGrap);
        InputSystem->BindAction(IA_LeftIdexCurl, ETriggerEvent::Triggered, this, &AVRPlayer::LeftIndexCurl);
        InputSystem->BindAction(IA_RightGrap, ETriggerEvent::Triggered, this, &AVRPlayer::RightGrap);
        InputSystem->BindAction(IA_RightIdexCurl, ETriggerEvent::Triggered, this, &AVRPlayer::RightIndexCurl);

        //Graps -> Idle Animation
        InputSystem->BindAction(IA_LeftGrap, ETriggerEvent::Completed, this, &AVRPlayer::LeftGrapUp);
        InputSystem->BindAction(IA_LeftIdexCurl, ETriggerEvent::Completed, this, &AVRPlayer::LeftIndexCurlUp);
        InputSystem->BindAction(IA_RightGrap, ETriggerEvent::Completed, this, &AVRPlayer::RightGrapUp);
        InputSystem->BindAction(IA_RightIdexCurl, ETriggerEvent::Completed, this, &AVRPlayer::RightIndexCurlUp);

        //Item
        InputSystem->BindAction(IA_ItemMenu, ETriggerEvent::Started, this,
            &AVRPlayer::OnItemMenu);
        InputSystem->BindAction(IA_ItemInteraction, ETriggerEvent::Triggered, this, &AVRPlayer::ItemInter);
        InputSystem->BindAction(IA_ItemInteraction, ETriggerEvent::Completed, this, &AVRPlayer::ItemInterUp);
        InputSystem->BindAction(IA_ItemTogle, ETriggerEvent::Triggered, this, &AVRPlayer::ItemTogle);
    }
}

void AVRPlayer::Move(const FInputActionValue& InputValue)
{
    FVector2d Value = InputValue.Get<FVector2d>();

    FVector Dir = VRCam->GetForwardVector() * Value.X + VRCam->GetRightVector() * Value.Y;
    AddMovementInput(Dir);
}

void AVRPlayer::Turn(const FInputActionValue& InputValue)
{
    FVector2d Value = InputValue.Get<FVector2d>();
    AddControllerPitchInput(Value.Y);
    AddControllerYawInput(Value.X);
}

void AVRPlayer::LeftGrap(const FInputActionValue& InputValue)
{
    AnimSet(1, InputValue.Get<float>(), true);
}

void AVRPlayer::LeftIndexCurl(const FInputActionValue& InputValue)
{
    AnimSet(2, InputValue.Get<float>(), true);
}

void AVRPlayer::RightGrap(const FInputActionValue& InputValue)
{
    AnimSet(3, InputValue.Get<float>(), false);
}

void AVRPlayer::RightIndexCurl(const FInputActionValue& InputValue)
{
    AnimSet(4, InputValue.Get<float>(), false);
}

void AVRPlayer::LeftGrapUp(const FInputActionValue& InputValue)
{
    AnimSet(1, InputValue.Get<float>(), true);
}

void AVRPlayer::LeftIndexCurlUp(const FInputActionValue& InputValue)
{
    AnimSet(2, InputValue.Get<float>(), true);
}

void AVRPlayer::RightGrapUp(const FInputActionValue& InputValue)
{
    AnimSet(3, InputValue.Get<float>(), false);
}

void AVRPlayer::RightIndexCurlUp(const FInputActionValue& InputValue)
{
    AnimSet(4, InputValue.Get<float>(), false);
}

void AVRPlayer::AnimSet(int Anim, float Value, bool isMirror)
{
    switch (Anim)
    {
    case 1:
        LeftHandAnim->PoseAlphaGrsap = Value;
        LeftHandAnim->bMirror = isMirror;
        break;
    case 2:
        LeftHandAnim->PoseAlphaIndexCurl = Value;
        LeftHandAnim->bMirror = isMirror;
        break;
    case 3:
        RightHandAnim->PoseAlphaGrsap = Value;
        RightHandAnim->bMirror = isMirror;
        break;
    case 4:
        RightHandAnim->PoseAlphaIndexCurl = Value;
        RightHandAnim->bMirror = isMirror;
        break;
    default:
        break;
    }
}

void AVRPlayer::OnItemMenu(const struct FInputActionValue& InputValue)
{
    //탭 또는 오른쪽 스틱 버튼이 눌린다면
    //아이템 UI 창이 열리지 않은 상태이면
    //if()

    //아이템 UI창을 띄워줌
}

//After SetVisibility -> SetCollisionEnnabled
void AVRPlayer::ItemInter(const struct FInputActionValue& InputValue)
{
    if (bHandSpear && !Spear->IsVisible())
    {
        ItemCollisionOnOff(1);
    }

    if(bHandPick &&!PickItem->IsVisible())
    {
        ItemCollisionOnOff(2);
    }

    if (bHandAxe && !Axe->IsVisible())
    {
        ItemCollisionOnOff(3);
    }

    if (bHandBow && !Bow->IsVisible())
    {
        ItemCollisionOnOff(4);
    }


}

void AVRPlayer::ItemInterUp(const struct FInputActionValue& InputValue)
{
    if (Spear->IsVisible())
    {
        ItemCollisionOnOff(1);
    }

    else if (PickItem->IsVisible())
    {
        ItemCollisionOnOff(2);
    }

    else if (Axe->IsVisible())
    {
        ItemCollisionOnOff(3);
    }

    else if (Bow->IsVisible())
    {
        ItemCollisionOnOff(4);
    }
}

void AVRPlayer::ItemTogle(const struct FInputActionValue& InputValue)
{
    bool value = InputValue.Get<bool>();

    //Item All Visible False
    ItemVisibleAllFalse();

    if (value)
    {
        if (ItemIndex == ItemArray.Num())
        {
            ItemIndex = ItemArray.Num();
            ItemArray[ItemArray.Num()];
            //SetItem(ItemArray[ItemIndex]->ItemNum);
        }
        ItemArray[ItemIndex + 1];
        ItemIndex++;
    }
    else
    {
        if (ItemIndex == 0)
        {
            ItemIndex = ItemArray.Num();
            ItemArray[ItemArray.Num()];
        }
        ItemArray[ ItemIndex - 1 ];
        ItemIndex--;
    }
}

void AVRPlayer::SetItem(int ItemNum)
{

}

void AVRPlayer::ItemCollisionOnOff(int ItemNum)
{
    switch (mItemState)
    {
    case EItemState::SetSpear:
        if (bSpear && !Spear->IsVisible())
        {
            //Spear->SetVisibility(true);
        }
        else 
        {
            //Spear->SetVisibility(false);
        }
        break;
    case EItemState::SetPick:
        if (bPick && !PickItem->IsVisible())
        {
            //PickItem->SetVisibility(true);
        }
        else
        {
            //PickItem->SetVisibility(false);
        }
        break;
    case EItemState::SetAxe:
        if (bAxe && !Axe->IsVisible())
        {
            //Axe->SetVisibility(true);
        }
        else
        {
            //Axe->SetVisibility(false);
        }
        break;
    case EItemState::SetBow:
        if (bBow && !Bow->IsVisible())
        {
            //Bow->SetVisibility(true);
        }
        else
        {
            //Bow->SetVisibility(false);
        }
        break;
    default:
        break;
    }
}

void AVRPlayer::TestItemPush()
{
    int num = FMath::RandRange(1, 3);

    switch (num)
    {
    case 1:
//         ItemArray.Add(Spear);
//         ItemArray.Add(Axe);
//         ItemArray.Add(Bow);
//         ItemArray.Add(PickItem);
        break;
    case 2:
//         ItemArray.Add(Bow);
//         ItemArray.Add(PickItem);
//         ItemArray.Add(Axe);
//         ItemArray.Add(Spear);
        break;
    case 3:
//         ItemArray.Add(PickItem);
//         ItemArray.Add(Spear);
//         ItemArray.Add(Axe);
//         ItemArray.Add(Bow);
        break;
    default:
        break;
    }
}

void AVRPlayer::ItemVisibleAllFalse()
{
    Spear->SetVisibility(false);
    PickItem->SetVisibility(false);
    Axe->SetVisibility(false);
    Bow->SetVisibility(false);
}
