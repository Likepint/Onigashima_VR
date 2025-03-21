#pragma once

#include "CoreMinimal.h"
#include "PJS/Components/CBaseComponent.h"
#include "CBuildComponent.generated.h"

UCLASS()
class ONIGASHIMA_API UCBuildComponent : public UCBaseComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Material")
	TArray<class UMaterialInstance*> Materials;

private:
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputAction* IA_Build;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputAction* IA_Select;
	
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

	void LoopBuild();
	void StopBuild();

	void Delay();

	void ResetBuild();

	void SpawnMesh();
	void ChangeMeshOutLine(bool bGreen);

private:
	class UCameraComponent* Camera;
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UStaticMesh* foundation;

private:
	bool bOnBuildMode = false;
	bool bCanBuild = false;
	bool bHit;

	int32 BuildID;

	FTransform BuildTransform;

	FTimerHandle BuildHandle;
};
