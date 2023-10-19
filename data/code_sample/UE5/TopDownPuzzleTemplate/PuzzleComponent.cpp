// Copyright David Xu - davidx@usc.edu

#include "PuzzleComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UPuzzleComponent::UPuzzleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPuzzleComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Set the output of the puzzle
void UPuzzleComponent::SetOutputActive(bool bActive)
{
	if (bActive == bIsOutputActive)
	{
		return;
	}
	else
	{
		bIsOutputActive = bActive;
	}

	if (AActor* OutActor = OutputActor.Get())
	{
		if (UPuzzleComponent* PuzzleComp = OutActor->FindComponentByClass<UPuzzleComponent>())
		{
			PuzzleComp->NativeReceiveInput(GetOwner(), bIsOutputActive);	
		}
	}
	
}

// Reset the puzzle component
void UPuzzleComponent::PuzzleReset()
{
	SetOutputActive(false);
	OnPuzzleReset.Broadcast();
}

// Receive input from other puzzle components
void UPuzzleComponent::NativeReceiveInput(AActor* InputActor, bool bIncomingValue)
{
	OnReceiveInput.Broadcast(InputActor, bIncomingValue);
}


// Called every frame
void UPuzzleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPuzzleComponent::ChangeOutputActor(AActor* MyActor)
{
	OutputActor = MyActor;
	if (OutputActor != nullptr && bIsOutputActive)
	{
		if (AActor* OutActor = OutputActor.Get())
		{
			if (UPuzzleComponent* PuzzleComp = OutActor->FindComponentByClass<UPuzzleComponent>())
			{
				PuzzleComp->NativeReceiveInput(GetOwner(), bIsOutputActive);
			}
		}
	}
}

void UPuzzleComponent::DebugDrawOutput()
{

#if ENABLE_DRAW_DEBUG
	if (AActor* OutActor = OutputActor.Get())
	{
		const FColor DrawColor = bIsOutputActive ? FColor::Green : FColor::Black;
		DrawDebugDirectionalArrow(GetWorld(), GetOwner()->GetActorLocation(), OutActor->GetActorLocation(), 150.0f, DrawColor);
	}

	if (IsRegistered())
	{
		DrawDebugString(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetName(), 0, FColor::White, 0.1f);
	}
#endif

}

