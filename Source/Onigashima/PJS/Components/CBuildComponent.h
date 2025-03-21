#pragma once

#include "CoreMinimal.h"
#include "PJS/Components/CBaseComponent.h"
#include "CBuildComponent.generated.h"

UCLASS()
class ONIGASHIMA_API UCBuildComponent : public UCBaseComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputAction* IA_Build;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputAction* IA_Select;

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
	void Select(const struct FInputActionValue& InVal);

private:
	void BuildMode();
	void DelayBuild();
	void LoopBuild();
	void StopBuild();
	void ResetBuild();

	void SpawnMesh();
	void SetOutLine(bool bGreen);

private:
	class UStaticMeshComponent* Mesh;

private:
	bool bOnBuildMode = false;
	bool bCanBuild = false;

	int32 BuildIndex = 0;

	FTransform BuildTransform;

	FTimerHandle hBuild;

};
