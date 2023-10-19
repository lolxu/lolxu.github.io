// Copyright David Xu - davidx@usc.edu

#include "InteractSubsystem.h"

#include "Logging/LogMacros.h"
#include "InteractComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TopDownCharacter.h"

void UInteractSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UInteractSubsystem::Deinitialize()
{
	Super::Deinitialize();

	InteractComponents.Empty();
}

void UInteractSubsystem::AddComponent(UInteractComponent* Component)
{
	InteractComponents.Add(Component);
}

void UInteractSubsystem::RemoveComponent(UInteractComponent* Component)
{
	InteractComponents.Remove(Component);
}

void UInteractSubsystem::PerformInteract()
{
	if (UInteractComponent* Component = BestCandidate.Get())
	{
		Component->NativeInteract();
	}
}

void UInteractSubsystem::Tick(float DeltaTime)
{
	// loop through all interact components
	BestCandidate = nullptr;
	if (ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0)) // Asumming single player
	{
		FVector PlayerPos = Character->GetActorLocation();
		float BestDistance = TNumericLimits<float>::Max();
		for (const auto& WeakPtr : InteractComponents)
		{
			if (UInteractComponent* Component = WeakPtr.Get())
			{
				// Turn Off Glow before doing anything else
				Component->SetGlowMaterial(false);

				float Distance = FVector::Distance(PlayerPos, Component->GetOwner()->GetActorLocation());
				if (Distance < BestDistance && Distance <= InteractDistance && Component->GetIsEnabled())
				{
					BestDistance = Distance;
					// Check angle of the interactable object towards the player
					FVector PlayerForward = Character->GetActorForwardVector();
					PlayerForward.Normalize();
					FVector TorchForward = Component->GetOwner()->GetActorForwardVector();
					TorchForward.Normalize();

					// Fix this
					float CurrentDotProduct = FVector::DotProduct(PlayerForward, TorchForward);
					float TempAngle = acos(CurrentDotProduct) * (180.0f / PI);

					// UE_LOG(LogTemp, Warning, TEXT("The angle value is: %f"), TempAngle);
					
					if (TempAngle >= InteractAngle)
					{
						// UE_LOG(LogTemp, Warning, TEXT("The angle value is: %f"), TempAngle);
						BestCandidate = WeakPtr;
					}
				}
			}
		}

		if (BestCandidate != nullptr)
		{
			// Turn on glow on the best candidate once it's found
			BestCandidate.Get()->SetGlowMaterial(true);
		}
	}
}

TStatId UInteractSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UInteractSubsystem, STATGROUP_Tickables);
}

TWeakObjectPtr<class UInteractComponent> UInteractSubsystem::GetBestCandidate()
{
	return BestCandidate;
}

bool UInteractSubsystem::DoesSupportWorldType(EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}
