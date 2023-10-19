// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "TopDownCharacter.h"
#include "Engine/World.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HUDWidget.h"

#include "InteractSubsystem.h"

ATopDownPlayerController::ATopDownPlayerController()
{
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATopDownPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

// When possess, create a new HUD Widget object and add to viewport
void ATopDownPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = NewObject<UHUDWidget>(this, HUDWidgetClass);
		HUDWidgetInstance->AddToViewport();
	}
}

void ATopDownPlayerController::OnJumpAction()
{
	if (ACharacter* MyCharacter = GetCharacter())
	{
		if (UCharacterMovementComponent* MyCMC = MyCharacter->GetCharacterMovement())
		{
			MyCMC->DoJump(false);
		}
	}
}

void ATopDownPlayerController::OnInteractAction()
{
	if (UInteractSubsystem* Subsystem = GetWorld()->GetSubsystem<UInteractSubsystem>())
	{
		Subsystem->PerformInteract();
	}
}

void ATopDownPlayerController::OnToggleCrouch()
{
	if (ACharacter* MyCharacter = GetCharacter())
	{
		if (!MyCharacter->bIsCrouched)
		{
			MyCharacter->Crouch();
		}
		else
		{
			MyCharacter->UnCrouch();
		}
	}
}

void ATopDownPlayerController::OnDashAction()
{
	if (ATopDownCharacter* MyCharacter = Cast<ATopDownCharacter>(GetPawn()))
	{
		MyCharacter->StartDash();
	}
}

void ATopDownPlayerController::OnMoveForward(const FInputActionInstance& Instance)
{
	if (APawn* MyPawn = GetPawn()) // putting this in if checks for the nullptr (failable expression)
	{
		if (ATopDownCharacter* MyCharacter = Cast<ATopDownCharacter>(MyPawn))
		{
			if (!MyCharacter->GetIsDashing())
			{
				float AxisValue = Instance.GetValue().Get<float>();
				MyPawn->AddMovementInput(FVector::ForwardVector, AxisValue);
			}
			
		}
		
	}
}

void ATopDownPlayerController::OnMoveRight(const FInputActionInstance& Instance)
{
	if (APawn* MyPawn = GetPawn()) // putting this in if checks for the nullptr (failable expression)
	{
		if (ATopDownCharacter* MyCharacter = Cast<ATopDownCharacter>(MyPawn))
		{
			if (!MyCharacter->GetIsDashing())
			{
				float AxisValue = Instance.GetValue().Get<float>();
				MyPawn->AddMovementInput(FVector::RightVector, AxisValue);
			}
		}
	}
}

void ATopDownPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::OnMoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::OnMoveRight);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::OnJumpAction);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::OnInteractAction);
		EnhancedInputComponent->BindAction(ToggleCrouchAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::OnToggleCrouch);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::OnDashAction);
	}
}


