// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "VRPlayer.generated.h"

UENUM()
enum class EItemState :uint8
{
	NoItem UMETA(DisplayName = "¸Ç¼Õ"),
	SetSpear UMETA(DisplayName = "Ã¢"),
	SetPick UMETA(DisplayName = "°î±ªÀÌ"),
	SetAxe UMETA(DisplayName = "µµ³¢"),
	SetBow UMETA(DisplayName = "È°")
};

UCLASS()
class ONIGASHIMA_API AVRPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: //Camera
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* VRCam;

public: //Player Input
 	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_VRInput;
 	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Move;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_Turn;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_LeftGrap;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_LeftIdexCurl;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_RightGrap;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_RightIdexCurl;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_ItemMenu;
	UPROPERTY(EditDefaultsOnly,Category = Input)
	class UInputAction* IA_ItemInteraction;
	UPROPERTY(EditDefaultsOnly,Category = Input)
	class UInputAction* IA_ItemTogle;

	//moving
	void Move(const struct FInputActionValue& InputValue);
	void Turn(const struct FInputActionValue& InputValue);
	
	//Down(Press)Button
	void LeftGrap(const struct FInputActionValue& InputValue);
	void LeftIndexCurl(const struct FInputActionValue& InputValue);
	void RightGrap(const struct FInputActionValue& InputValue);
	void RightIndexCurl(const struct FInputActionValue& InputValue);

	//Up Button
	void LeftGrapUp(const struct FInputActionValue& InputValue);
	void LeftIndexCurlUp(const struct FInputActionValue& InputValue);
	void RightGrapUp(const struct FInputActionValue& InputValue);
	void RightIndexCurlUp(const struct FInputActionValue& InputValue);

	//Animation
	void AnimSet(int Anim, float Value, bool isMirror);

	//Item
	void OnItemMenu(const struct FInputActionValue& InputValue);
	void ItemInter(const struct FInputActionValue& InputValue);
	void ItemInterUp(const struct FInputActionValue& InputValue);
	void ItemTogle(const struct FInputActionValue& InputValue);

	void SetItem(int ItemNum);
	void ItemCollisionOnOff(int ItemNum);

public: //Hands
	UPROPERTY(EditDefaultsOnly)
	class UMotionControllerComponent* LeftSceneComp;
	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* LeftHandMesh;

	UPROPERTY(EditDefaultsOnly)
	class UMotionControllerComponent* RightSceneComp;
	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* RightHandMesh;

	class UCVRPlayerAnim* LeftHandAnim;
	class UCVRPlayerAnim* RightHandAnim;

public: //Widget
	UPROPERTY(EditDefaultsOnly)
	class UWidget* ItemMenuWidget;

public: //Item equipment
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* Spear;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* PickItem;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* Axe;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* Bow;

	// Get Item?
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = Bool)
	bool bSpear = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bool)
	bool bPick = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bool)
	bool bAxe = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bool)
	bool bBow = false;

	//Now In Hand Item?
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = Bool)
	bool bHandSpear = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bool)
	bool bHandPick = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bool)
	bool bHandAxe = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bool)
	bool bHandBow = false;

	TArray<class ACItem*> ItemArray;

	int ItemIndex = 0;

	//Item State
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FSM)
	EItemState mItemState = EItemState::NoItem;

	void TestItemPush();

	void ItemVisibleAllFalse();
};
