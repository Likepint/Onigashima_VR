// Fill out your copyright notice in the Description page of Project Settings.


#include "ODH/VRPlayer.h"
#include "Global.h"
#include "Camera/CameraComponent.h"
#include "PJS/Components/CBuildComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "CVRPlayerAnim.h"
#include "Components/StaticMeshComponent.h"
#include "MotionControllerComponent.h"
#include "CPick.h"
#include "CBow.h"
#include "CSpear.h"
#include "CAxe.h"
#include "Components/BoxComponent.h"
#include "CArrow.h"

// Sets default values
AVRPlayer::AVRPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //Camera Create
    VRCam = CreateDefaultSubobject<UCameraComponent>(L"VRCam");
    VRCam->SetupAttachment(RootComponent);
    VRCam->bUsePawnControlRotation = true;

    CHelpers::CreateActorComponent<UCBuildComponent>(this, &Build, "Build");

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

    ConstructorHelpers::FObjectFinder<UInputAction> Temp_ItemIndexPlus(L"/Script/EnhancedInput.InputAction'/Game/ODH/Input/IA_ItemIndexPlus.IA_ItemIndexPlus'");
    if (Temp_ItemIndexPlus.Succeeded())
    {
        IA_ItemIndexPlus = Temp_ItemIndexPlus.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> Temp_ItemIndexMinus(L"/Script/EnhancedInput.InputAction'/Game/ODH/Input/IA_ItemIndexMinus.IA_ItemIndexMinus'");
    if (Temp_ItemIndexMinus.Succeeded())
    {
        IA_ItemIndexMinus = Temp_ItemIndexMinus.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> Temp_Jump(L"/Script/EnhancedInput.InputAction'/Game/ODH/Input/IA_VRJump.IA_VRJump'");
    if (Temp_Jump.Succeeded())
    {
        IA_Jump = Temp_Jump.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> Temp_YButton(L"/Script/EnhancedInput.InputAction'/Game/ODH/Input/IA_YButton.IA_YButton'");
    if (Temp_YButton.Succeeded())
    {
        IA_YButton = Temp_YButton.Object;
    }

    // LeftHand Create
    LeftSceneComp = CreateDefaultSubobject<UMotionControllerComponent>(L"ControllerLftGrip");
    LeftSceneComp->SetupAttachment(RootComponent);
    
    LeftHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(L"LeftHand");
    LeftHandMesh->SetupAttachment(LeftSceneComp);

    ConstructorHelpers::FObjectFinder<USkeletalMesh> Temp_LeftHand(L"/Script/Engine.SkeletalMesh'/Game/ODH/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'");
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

    ConstructorHelpers::FObjectFinder<USkeletalMesh> Temp_RightHand(L"/Script/Engine.SkeletalMesh'/Game/ODH/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'");
    if (Temp_RightHand.Succeeded())
    {
        RightHandMesh->SetSkeletalMesh(Temp_RightHand.Object);
        RightHandMesh->SetRelativeRotation(FRotator(0, -90, 0));
    }

    //equipment
    Spear = CreateDefaultSubobject<UStaticMeshComponent>(L"SpearComp");
    Spear->SetupAttachment(RightHandMesh, L"hand_rSocket");

    ConstructorHelpers::FObjectFinder<UStaticMesh> Temp_Spear(L"/Script/Engine.StaticMesh'/Game/ODH/Old_Wooden_Pole_ueqfdi0ga/Old_Wooden_Pole_ueqfdi0ga_Low.Old_Wooden_Pole_ueqfdi0ga_Low'");
    if (Temp_Spear.Succeeded())
    {
        Spear->SetStaticMesh(Temp_Spear.Object);
        Spear->SetRelativeScale3D(FVector(0.2f));
        Spear->SetRelativeLocationAndRotation(FVector(-29, 0, 0), FRotator(0, 0, 90));
        
        SpearColli = CreateDefaultSubobject<UBoxComponent>(L"SpearCollision");
        SpearColli->SetupAttachment(Spear);
        SpearColli->SetRelativeLocation(FVector(0, 160, 5));
        SpearColli->SetBoxExtent(FVector(8.156206f, 77.76204f, 7.885468f));
        SpearColli->OnComponentBeginOverlap.AddDynamic(this, &AVRPlayer::SpearOverlap);
    }

    PickItem = CreateDefaultSubobject<UStaticMeshComponent>(L"PickComp");
    PickItem->SetupAttachment(RightHandMesh, L"hand_rSocket");
    PickItem->SetRelativeScale3D(FVector(0.2f));

    Axe = CreateDefaultSubobject<UStaticMeshComponent>(L"AxeComp");
    Axe->SetupAttachment(RightHandMesh, L"hand_rSocket");
    ConstructorHelpers::FObjectFinder<UStaticMesh> Temp_Axe(L"/Script/Engine.StaticMesh'/Game/ODH/Axe_ueqgcaifa/Medium/ueqgcaifa_tier_2.ueqgcaifa_tier_2'");
    if (Temp_Axe.Succeeded())
    {
        Axe->SetStaticMesh(Temp_Axe.Object);
        Axe->SetRelativeLocationAndRotation(FVector(-10, 0, 0), FRotator(90, 0, 180));

		AxeColli = CreateDefaultSubobject<UBoxComponent>(L"AxeCollision");
		AxeColli->SetupAttachment(Axe);
		AxeColli->SetRelativeLocationAndRotation(FVector(17, 4.838387f, 2.258435f), FRotator(0, 180, 90));
		AxeColli->SetBoxExtent(FVector(5.524121f, 1.973751f, 7.189121f));
        AxeColli->OnComponentBeginOverlap.AddDynamic(this, &AVRPlayer::AxeOverlap);
    }


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

    ItemVisibleAllFalse();

    ItemArray.Add(nullptr);

    LeftHandAnim = Cast<UCVRPlayerAnim>(LeftHandMesh->GetAnimInstance());
    RightHandAnim = Cast<UCVRPlayerAnim>(RightHandMesh->GetAnimInstance());

    CurHealth = MaxHealth;

    TestItemPush();

    for (int32 i = 0; i < MaxArrowCnt; i++)
    {
        FActorSpawnParameters params;
        params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        ACArrow* Ar = GetWorld()->SpawnActor<ACArrow>(Arrow,params);
        Ar->SetActive(false);
        ArrowPool.Add(Ar);
    }
}

// Called every frame
void AVRPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bRightBbutton && bRightTrigger && bRightGrap && !bMeshOn)
    {
        ItemCollisionOnOff(ItemIndex);
        bMeshOn = true;
    }

    if (Bow->IsVisible() && !bFindArrow && bLeftTrigger && bLeftGrap)
    {
        AimArrow();
    }
    
//     if (Bow->IsVisible() && !SpawnArrow && bLeftTrigger && bLeftGrap)
//     {
//         SpawnArrow = GetWorld()->SpawnActor<ACArrow>();
//         SpawnArrow->AttachToComponent(RightHandMesh, FAttachmentTransformRules::KeepRelativeTransform, L"index_03_lSocket");
//     }

    switch (PlayerState)
    {
    case EItemState::NoItem:
        ATK = 10;
    	break;
    case EItemState::SetSpear:
        ATK = 20;
        break;
    case EItemState::SetPick:
        ATK = 16;
        break;
    case EItemState::SetAxe:
        ATK = 18;
        break;
    case EItemState::SetBow:
        ATK = 20;
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
        InputSystem->BindAction(IA_Jump, ETriggerEvent::Started, this, &AVRPlayer::VRJump);

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
        InputSystem->BindAction(IA_ItemInteraction, ETriggerEvent::Started, this, &AVRPlayer::ItemInter);
        InputSystem->BindAction(IA_ItemInteraction, ETriggerEvent::Completed, this, &AVRPlayer::ItemInterUp);
        InputSystem->BindAction(IA_ItemIndexPlus, ETriggerEvent::Completed, this, &AVRPlayer::ItemIndexPlus);
        InputSystem->BindAction(IA_ItemIndexMinus, ETriggerEvent::Completed, this, &AVRPlayer::ItemIndexMinus);

        InputSystem->BindAction(IA_YButton, ETriggerEvent::Started, this, &AVRPlayer::YButtonDown);
        InputSystem->BindAction(IA_YButton, ETriggerEvent::Completed, this, &AVRPlayer::YButtonUp);

        // Build
        Build->OnBindEnhancedInputSystem(InputSystem);
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

void AVRPlayer::VRJump(const struct FInputActionValue& InputValue)
{
    Jump();
}

void AVRPlayer::LeftGrap(const FInputActionValue& InputValue)
{
    AnimSet(1, InputValue.Get<float>(), true);
    bLeftGrap = true;
}

void AVRPlayer::LeftIndexCurl(const FInputActionValue& InputValue)
{
    AnimSet(2, InputValue.Get<float>(), true);
    bLeftTrigger = true;
}

void AVRPlayer::RightGrap(const FInputActionValue& InputValue)
{
    AnimSet(3, InputValue.Get<float>(), false);
    bRightGrap = true;
}

void AVRPlayer::RightIndexCurl(const FInputActionValue& InputValue)
{
    AnimSet(4, InputValue.Get<float>(), false);
    bRightTrigger = true;
}

void AVRPlayer::YButtonDown(const struct FInputActionValue& InputValue)
{
    
}

void AVRPlayer::LeftGrapUp(const FInputActionValue& InputValue)
{
    AnimSet(1, InputValue.Get<float>(), true);
    bLeftGrap = false;
}

void AVRPlayer::LeftIndexCurlUp(const FInputActionValue& InputValue)
{
    AnimSet(2, InputValue.Get<float>(), true);
    bLeftTrigger= false;
}

void AVRPlayer::RightGrapUp(const FInputActionValue& InputValue)
{
    AnimSet(3, InputValue.Get<float>(), false);
    bRightGrap = false;
    RightGrapAllCheck();
}

void AVRPlayer::RightIndexCurlUp(const FInputActionValue& InputValue)
{
    AnimSet(4, InputValue.Get<float>(), false);
    bRightTrigger = false;
    RightGrapAllCheck();
}

void AVRPlayer::YButtonUp(const struct FInputActionValue& InputValue)
{
    
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
    bRightBbutton = true;
}

void AVRPlayer::ItemInterUp(const struct FInputActionValue& InputValue)
{
    bRightBbutton = false;
    RightGrapAllCheck();
}

void AVRPlayer::ItemIndexPlus(const FInputActionValue& InputValue)
{
	if (!bMeshOn)
	{
		ItemVisibleAllFalse();

		if (ItemIndex == ItemArray.Num() - 1)
		{
			ItemIndex = 0;
		}
		else
		{
			ItemIndex++;
		}
	}
}

void AVRPlayer::ItemIndexMinus(const FInputActionValue& InputValue)
{
	if (!bMeshOn)
	{
		ItemVisibleAllFalse();

		if (ItemIndex == 0)
		{
			ItemIndex = ItemArray.Num() - 1;
		}
		else
		{
			ItemIndex--;
		}
	}
}

void AVRPlayer::ItemCollisionOnOff(int ItemNum)
{
    if (ItemNum == 0)
        return;

//     switch (PlayerState)
//     {
//     case EItemState::SetBow:
//         Bow->SetVisibility(true);
//         break;
//     case EItemState::SetSpear:
//         Spear->SetVisibility(true);
//         SpearColli->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
//         break;
//     case EItemState::SetAxe:
//         Axe->SetVisibility(true);
//         AxeColli->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
//         break;
//     case EItemState::SetPick:
//         PickItem->SetVisibility(true);
//         /*PickColli->SetCollisionEnabled(ECollisionEnabled::QueryOnly);*/
//         break;
//     default:
//         break;
//     }

    switch (ItemNum)
    {
    case 1:
        Bow->SetVisibility(true);
        break;
    case 2:
        Spear->SetVisibility(true);
        SpearColli->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        break;
    case 3:
        Axe->SetVisibility(true);
        AxeColli->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        break;
    case 4:
        PickItem->SetVisibility(true);
        /*PickColli->SetCollisionEnabled(ECollisionEnabled::QueryOnly);*/
        break;
    default:
        break;
    }


//     else if (ItemArray[ItemNum]->IsVisible())
//     {
//         ItemArray[ItemNum]->SetVisibility(false);
//         
//     }
// 
//     else
//     {
//         ItemArray[ItemNum]->SetVisibility(true);
//     }
}

void AVRPlayer::SpearOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    auto actor = Cast<AActor>(OtherActor);

    if(actor)
    {
        GEngine->AddOnScreenDebugMessage(20, 3.0f, FColor::Red, TEXT("Spear Collision"));
    }
}

void AVRPlayer::AxeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    auto actor = Cast<AActor>(OtherActor);

    if (actor)
    {
        GEngine->AddOnScreenDebugMessage(20, 3.0f, FColor::Red, TEXT("Axe Collision"));
    }
}

void AVRPlayer::AimArrow()
{
    for (int32 i = 0; i < ArrowPool.Num(); i++)
    {
        if (!ArrowPool[i]->ArrowMesh->GetVisibleFlag())
        {
            bFindArrow = true;

            /*ArrowPool[i]->SetActive(true);*/

            ArrowPool[i]->AttachToComponent(LeftHandMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("index_03_lSocket"));

            break;
        }
    }
}

void AVRPlayer::RightGrapAllCheck()
{
    if(ItemIndex != 0)
        ItemArray[ItemIndex]->SetVisibility(false);

    bMeshOn = false;
}

void AVRPlayer::TestItemPush()
{
    ItemArray.Add(Bow);
    ItemArray.Add(Spear);
    ItemArray.Add(Axe);
    ItemArray.Add(PickItem);

//     int num = FMath::RandRange(1, 3);
// 
//     switch (num)
//     {
//     case 1:
//         ItemArray.Add(Spear);
//         ItemArray.Add(Axe);
//         ItemArray.Add(Bow);
//         ItemArray.Add(PickItem);
//         break;
//     case 2:
//         ItemArray.Add(Bow);
//         ItemArray.Add(PickItem);
//         ItemArray.Add(Axe);
//         ItemArray.Add(Spear);
//         break;
//     case 3:
//         ItemArray.Add(PickItem);
//         ItemArray.Add(Spear);
//         ItemArray.Add(Axe);
//         ItemArray.Add(Bow);
//         break;
//     default:
//         break;
//     }
}

void AVRPlayer::ItemVisibleAllFalse()
{
    Spear->SetVisibility(false);
    PickItem->SetVisibility(false);
    Axe->SetVisibility(false);
    Bow->SetVisibility(false);

    SpearColli->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    AxeColli->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
