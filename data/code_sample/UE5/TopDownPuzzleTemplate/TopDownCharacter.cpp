// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownCharacter.h"

#include "VectorTypes.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ATopDownCharacter::ATopDownCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATopDownCharacter::Tick(float DeltaSeconds)
{
	// Dash Stuff here
	if (bIsDashing)
	{
		AddMovementInput(GetActorForwardVector(), 1.0f);
	}

	// Invulnerability check here
	for (int i = InvulnerableRequestors.Num() - 1; i >= 0; i--)
	{
		if (!InvulnerableRequestors[i].IsValid())
		{
			InvulnerableRequestors.RemoveAt(i);
		}
	}
	
	Super::Tick(DeltaSeconds);
	
}

void ATopDownCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

bool ATopDownCharacter::CanCrouch() const
{
	if (bIsDashing)
	{
		return false;
	}
	else
	{
		return Super::CanCrouch();
	}
}

bool ATopDownCharacter::ShouldTakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const
{
	bool bTakeDamage = Super::ShouldTakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (bIsDead)
	{
		return false;
	}

	if (InvulnerableRequestors.Num() > 0)
	{
		return false;
	}
	
	return bTakeDamage;
}

float ATopDownCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float CurrentDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CurrentDamage > 0.0f)
	{
		CurrentHealth -= CurrentDamage;
	}

	if (CurrentHealth <= 0.0f)
	{
		bIsDead = true;
		if (UAnimMontage* MontageToPlay = DeathMontage.Get())
		{
			if (!bHasDied)
			{
				bHasDied = true;
				DeathMontageLength = GetMesh()->GetAnimInstance()->Montage_Play(MontageToPlay);
				// Get this pawn's controller as a APlayerController
				APlayerController* PC = GetController<APlayerController>();
				// Call disable input on the controller (it's silly, but you have to pass in itself)
				PC->DisableInput(PC);

				// Setup a timer to deactivate mesh
				GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &ATopDownCharacter::DeactivateSkeletalMesh, DeathMontageLength - 0.25f, false);
			}
		}
	}
	
	return CurrentDamage;
}

void ATopDownCharacter::OnEnterBlueTrigger()
{
	NumBlueVolumes++;
	if (NumBlueVolumes == 1)
	{
		GetMesh()->SetVectorParameterValueOnMaterials(BodyColorParamName, FVector(BlueColor.R, BlueColor.G, BlueColor.B));
	}
}

void ATopDownCharacter::OnExitBlueTrigger()
{
	NumBlueVolumes--;
	if (NumBlueVolumes == 0)
	{
		GetMesh()->SetVectorParameterValueOnMaterials(BodyColorParamName, FVector(DefaultColor.R, DefaultColor.G, DefaultColor.B));
	}
}

void ATopDownCharacter::StartDash()
{
	if (!bIsDashing)
	{
		if (UAnimMontage* MontageToPlay = DashMontage.Get())
		{
			DashMontageLength = GetMesh()->GetAnimInstance()->Montage_Play(MontageToPlay);
			bIsDashing = true;
			if (UCharacterMovementComponent* MyCMC = GetCharacterMovement())
			{
				MyCMC->MaxWalkSpeed *= DashSpeedMultiplier;
				MyCMC->MaxAcceleration *= DashAccelMultiplier;

				// Check for crouching to uncrouch
				if (MyCMC->IsCrouching())
				{
					UnCrouch();
				}
			}
			GetWorldTimerManager().SetTimer(DashTimerHandle, this, &ATopDownCharacter::EndDash, DashMontageLength, false);
		}
	}
}

bool ATopDownCharacter::GetIsDashing()
{
	return bIsDashing;
}

void ATopDownCharacter::AddInvulnerableRequestor(UObject* Object)
{
	InvulnerableRequestors.Add(Object);
}
void ATopDownCharacter::RemoveInvulnerableRequestor(UObject* Object)
{
	InvulnerableRequestors.Remove(Object);
}

void ATopDownCharacter::BodyColorTurnBlue()
{
	GetMesh()->SetVectorParameterValueOnMaterials(BodyColorParamName, FVector(BlueColor.R, BlueColor.G, BlueColor.B));
}
void ATopDownCharacter::BodyColorTurnNormal()
{
	GetMesh()->SetVectorParameterValueOnMaterials(BodyColorParamName, FVector(DefaultColor.R, DefaultColor.G, DefaultColor.B));
}

void ATopDownCharacter::EndDash()
{
	if (UCharacterMovementComponent* MyCMC = GetCharacterMovement())
	{
		MyCMC->MaxWalkSpeed /= DashSpeedMultiplier;
		MyCMC->MaxAcceleration /= DashAccelMultiplier;
	}
	bIsDashing = false;
}

void ATopDownCharacter::DeactivateSkeletalMesh()
{
	GetMesh()->Deactivate();
}
