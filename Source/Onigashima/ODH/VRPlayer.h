﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "CItem.h"
#include "CAxe.h"
#include "VRPlayer.generated.h"

UENUM()
enum class EItemState :uint8
{
	NoItem UMETA(DisplayName = "맨손"),
	SetSpear UMETA(DisplayName = "창"),
	SetPick UMETA(DisplayName = "곡괭이"),
	SetAxe UMETA(DisplayName = "도끼"),
	SetBow UMETA(DisplayName = "활")
};

UCLASS()
class ONIGASHIMA_API AVRPlayer : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	class UCBuildComponent* Build;

	UPROPERTY(VisibleAnywhere)
	class UCInventoryComponent* Inventory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACMenu> MenuFactory;

	UPROPERTY(VisibleAnywhere)
	class ACMenu* Menu;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACItem_Bow> BowClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACItem_Axe> AxeClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACItem_Pick> PickClass;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* VRCam;

private:
	int32 Health = 20;
	int32 ATK;

	EItemState PlayerState = EItemState::NoItem;

public:
	void OnDamagePlayer(int32 damage);

private:
	//moving
	void Move(const struct FInputActionValue& InputValue);
	void Turn(const struct FInputActionValue& InputValue);

	//Jump
	void VRJump(const struct FInputActionValue& InputValue);
	
	//Down(Press)Button
	void LeftGrap(const struct FInputActionValue& InputValue);
	void LeftIndexCurl(const struct FInputActionValue& InputValue);
	void RightGrap(const struct FInputActionValue& InputValue);
	void RightIndexCurl(const struct FInputActionValue& InputValue);
	void YButtonDown(const struct FInputActionValue& InputValue);

	//Up Button
	void LeftGrapUp(const struct FInputActionValue& InputValue);
	void LeftIndexCurlUp(const struct FInputActionValue& InputValue);
	void RightGrapUp(const struct FInputActionValue& InputValue);
	void RightIndexCurlUp(const struct FInputActionValue& InputValue);
	void YButtonUp(const struct FInputActionValue& InputValue);

	//Animation
	void AnimSet(int32 Anim, float Value, bool isMirror);

	//Item
	/*void OnItemMenu(const struct FInputActionValue& InputValue);*/
	void ItemInter(const struct FInputActionValue& InputValue);
	void ItemInterUp(const struct FInputActionValue& InputValue);
	void ItemIndexPlus(const struct FInputActionValue& InputValue);
	void ItemIndexMinus(const struct FInputActionValue& InputValue);

	void ItemCollisionOnOff(int32 ItemNum);

	//Item Collision Overlap
// 	UFUNCTION()
// 	void SpearOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
// 
// 	UFUNCTION()
// 	void AxeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
// 
// 	UFUNCTION()
// 	void PickOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Left Hand Collision Overlap
	UFUNCTION()
	void LeftHandBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void LeftHandEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public: //HandScene
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UMotionControllerComponent* LeftSceneComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UMotionControllerComponent* RightSceneComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UWidgetInteractionComponent* WidgetInteractionComponent;


protected: //Hands
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class USkeletalMeshComponent* LeftHandMesh;
	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* LeftHandColli;

	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* RightHandMesh;

	class UCVRPlayerAnim* LeftHandAnim;
	class UCVRPlayerAnim* RightHandAnim;

private: //Widget
	UPROPERTY(EditDefaultsOnly)
	class UWidget* ItemMenuWidget;

private: //Item equipment
// 	UPROPERTY(EditDefaultsOnly)
// 	class UStaticMeshComponent* Spear;
// 	UPROPERTY(EditDefaultsOnly)
// 	class UBoxComponent* SpearColli;
// 
// 	UPROPERTY(EditDefaultsOnly)
// 	class UStaticMeshComponent* PickItem;
// 	UPROPERTY(EditDefaultsOnly)
// 	class UBoxComponent* PickColli;
// 
// 	UPROPERTY(EditDefaultsOnly)
// 	class UStaticMeshComponent* Axe;
// 	UPROPERTY(EditDefaultsOnly)
// 	class UBoxComponent* AxeColli;
// 	
// 	UPROPERTY(EditDefaultsOnly)
// 	class UStaticMeshComponent* Bow;
// 	UPROPERTY(EditDefaultsOnly)
// 	class UBoxComponent* BowColli;

	TArray<class ACItem*> ItemArray;

	UPROPERTY(EditDefaultsOnly,Category=Items)
	TSubclassOf<class ACAxe> CAxe;

	UPROPERTY(EditDefaultsOnly,Category=Items)
	TSubclassOf<class ACSpear> CSpear;

	UPROPERTY(EditDefaultsOnly,Category=Items)
	TSubclassOf<class ACBow> CBow;

	UPROPERTY(EditDefaultsOnly,Category=Items)
	TSubclassOf<class ACPick> CPick;

	ACAxe* SpawnAxe;
	ACSpear* SpawnSpear;
	ACBow* SpawnBow;
	ACPick* SpawnPick;

	void GetAddress(ACItem* Item,int32 ItemNum);

	void SetItems(TSubclassOf<class ACItem> ItemName, FVector SetPos, FRotator SetRot);

	UPROPERTY(EditDefaultsOnly)
	class UArrowComponent* ShootPos;

	FVector DefaultPos = FVector(-8.455319f, -60.162721f, 16.62593f);
	FVector MaxPos = FVector(-11.57968f, -82.393703f, 18.590003f);

	float CurDistance = 0.0f;
	float MinDistance = 15;
	float MaxDistance = 50;
	float Alpha;

	UPROPERTY(EditAnywhere, Category = Arrow)
	TSubclassOf<class ACArrow> Arrow;

	ACArrow* SpawnArrow;

	int32 MaxArrowCnt = 5;
	TArray<class ACArrow*> ArrowPool;

	int32 ArrowIndex = 0;

	bool bFindArrow = false;

	void AimArrow();
	bool bDetectBowString = false;

	bool bRightTrigger = false;
	bool bRightGrap = false;
	bool bRightBbutton = false;
	bool bMeshOn = false;

	bool bLeftGrap = false;
	bool bLeftTrigger = false;

	void RightGrapAllCheck();

	/*TArray<UStaticMeshComponent*> ItemArray;*/

	int32 ItemIndex = 0;

	void TestItemPush();

	void ItemVisibleAllFalse();

private:
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* ArrowSound;

private: //Player Input
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
	class UInputAction* IA_ItemIndexPlus;
	UPROPERTY(EditDefaultsOnly,Category = Input)
	class UInputAction* IA_ItemIndexMinus;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_Jump;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_YButton;
};
