// Copyright David Xu - davidx@usc.edu


#include "PuzzleRotate.h"
#include "PuzzleComponent.h"

// Sets default values
APuzzleRotate::APuzzleRotate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	 
	// Creating root component
	RootComponent = CreateDefaultSubobject<UBillboardComponent>("Root");
	PuzzleComponent = CreateDefaultSubobject<UPuzzleComponent>("Puzzle");
}

// Called when the game starts or when spawned
void APuzzleRotate::BeginPlay()
{
	Super::BeginPlay();
	
	PuzzleComponent->OnReceiveInput.AddDynamic(this, &APuzzleRotate::OnReceiveInput);
	for (TSoftObjectPtr<AActor> PuzzleActor : InputActors)
	{
		if (UPuzzleComponent* PuzzleComp = PuzzleActor.Get()->GetComponentByClass<UPuzzleComponent>())
		{
			PuzzleComp->ChangeOutputActor(nullptr);
		}
	}
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APuzzleRotate::OnRotateTimer, TimerDuration, true);
}

void APuzzleRotate::OnRotateTimer()
{
	if (InputActors.Num() > 0)
	{
		PuzzleComponent->PuzzleReset();
		int Index = 0;
		for (TSoftObjectPtr<AActor> PuzzleActor : InputActors)
		{
			if (UPuzzleComponent* PuzzleComp = PuzzleActor.Get()->GetComponentByClass<UPuzzleComponent>())
			{
				if (Index == CurrentIndex)
				{
					PuzzleComp->ChangeOutputActor(this);
				}
				else
				{
					PuzzleComp->ChangeOutputActor(nullptr);
				}
			}
			Index++;
		}
		CurrentIndex++;
		if (CurrentIndex == InputActors.Num())
		{
			CurrentIndex = 0;
		}
	}
}

// Called every frame
void APuzzleRotate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzleRotate::OnReceiveInput(AActor* InputActor, bool bValue)
{
	PuzzleComponent->SetOutputActive(bValue);
}

