// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "InputAction.h"

#include "TopDownPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	ATopDownPlayerController();

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> MoveRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> ToggleCrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> DashAction;

	class UHUDWidget* GetHUDWidget() const {return HUDWidgetInstance;}
	
protected:
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	// Override to include HUD stuff
	virtual void OnPossess(APawn* aPawn) override;

	// Movement Handlers
	void OnJumpAction();
	void OnInteractAction();
	void OnToggleCrouch();
	void OnDashAction();
	void OnMoveForward(const FInputActionInstance& Instance);
	void OnMoveRight(const FInputActionInstance& Instance);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDWidget> HUDWidgetClass;

	UPROPERTY(Transient)
	TObjectPtr<class UHUDWidget> HUDWidgetInstance;
};


