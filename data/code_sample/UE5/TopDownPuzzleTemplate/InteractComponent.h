// Copyright David Xu - davidx@usc.edu

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOPDOWN_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractComponent();

	virtual void NativeInteract();
	// Set glow material on interactable mesh
	void SetGlowMaterial(bool bTurnOn);
	bool GetIsEnabled();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName InteractGlowParameterName = FName(TEXT("InteractGlow"));

	// Value for Interact Glow
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector InteractGlowValue;

	UPROPERTY(BlueprintReadWrite)
	bool bIsEnabled = true;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// The delegate for on interacting with the component
	UPROPERTY(BlueprintAssignable)
	FInteractDelegate OnInteract;

	UFUNCTION(BlueprintCallable)
	virtual void SetIsEnabled(bool bEnabled);

	UMaterialInstance* MyMaterial;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
