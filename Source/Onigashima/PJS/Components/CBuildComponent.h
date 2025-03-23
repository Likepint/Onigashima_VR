#pragma once

#include "CoreMinimal.h"
#include "PJS/Components/CBaseComponent.h"
#include "CBuildComponent.generated.h"

USTRUCT()
struct FDetectBuild
{
	GENERATED_BODY()

public:
	bool bFound;

	FTransform Transform;

};

UCLASS()
class ONIGASHIMA_API UCBuildComponent : public UCBaseComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputAction* IA_OnBuild;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputAction* IA_Select;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputAction* IA_Build;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputAction* IA_Rotate;

private:
	UPROPERTY(EditDefaultsOnly)
	class UCBuildAsset* BuildAsset;

public:
	UCBuildComponent();

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void OnBindEnhancedInputSystem(class UEnhancedInputComponent* InEnhancedInput) override;

private:
	void BuildMode(const struct FInputActionValue& InVal);
	void SpawnBuild(const struct FInputActionValue& InVal);
	void SelectOrRotate(const struct FInputActionValue& InVal);
	void Rotate(const struct FInputActionValue& InVal);

private:
	void DelayBuild();
	void LoopBuild();
	void StopBuild();
	void ResetBuild();

	void SpawnMesh();
	void SetOutLine(bool bGreen);

	void ChangeMesh();

public:
	FDetectBuild GetDetectBuild(class AActor* InHitActor, class UPrimitiveComponent* InHitComponent);

private:
	class UStaticMeshComponent* Mesh;

private:
	bool bOnBuildMode = false;
	bool bCanBuild = false;

	int32 BuildID = 0;

	FTransform BuildTransform;

	FTimerHandle hBuild;

	bool bRotate = false;

};
