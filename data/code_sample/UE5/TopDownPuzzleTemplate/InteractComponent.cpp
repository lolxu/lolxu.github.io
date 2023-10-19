// Copyright David Xu - davidx@usc.edu

#include "InteractComponent.h"
#include "InteractSubsystem.h"

// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// Add this interact component from array inside world subsystem
	if (UInteractSubsystem* Subsystem = GetWorld()->GetSubsystem<UInteractSubsystem>())
	{
		Subsystem->AddComponent(this);
	}

	//
}

void UInteractComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Remove this interact component from array inside world subsystem
	if (UInteractSubsystem* Subsystem = GetWorld()->GetSubsystem<UInteractSubsystem>())
	{
		Subsystem->RemoveComponent(this);
	}
}

void UInteractComponent::SetIsEnabled(bool bEnabled)
{
	bIsEnabled = bEnabled;
}

void UInteractComponent::SetGlowMaterial(bool bTurnOn)
{
	if (AActor* TorchActor = GetOwner())
	{
		if (UStaticMeshComponent* TorchMesh = TorchActor->GetComponentByClass<UStaticMeshComponent>())
		{
			if (bTurnOn)
			{
				TorchMesh->SetVectorParameterValueOnMaterials(InteractGlowParameterName, InteractGlowValue);
			}
			else
			{
				TorchMesh->SetVectorParameterValueOnMaterials(InteractGlowParameterName, FVector::Zero());
			}
		}
	}
}

bool UInteractComponent::GetIsEnabled()
{
	return bIsEnabled;
}

void UInteractComponent::NativeInteract()
{
	OnInteract.Broadcast();
}

// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
