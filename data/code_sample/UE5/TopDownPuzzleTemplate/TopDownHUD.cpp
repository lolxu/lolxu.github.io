// Copyright David Xu - davidx@usc.edu

#include "TopDownHUD.h"
#include "DrawDebugHelpers.h"
#include "PuzzleComponent.h"
#include "InteractSubsystem.h"
#include "InteractComponent.h"
#include "TopDownCharacter.h"
#include "Kismet/GameplayStatics.h"

static TAutoConsoleVariable<int32> CVarDebugPuzzles(
	TEXT("DebugPuzzles"),									 // Console command
	0,														 // Default value
	TEXT("Turns puzzle debug view on/off (off by default)"), // Help text
	ECVF_Default);											 // Flags

void ATopDownHUD::DrawHUD()
{
	Super::DrawHUD();
	// The code is commented out because the instruction said so...
	// DrawText(TEXT("Hello World!"), FLinearColor::White, 0.0f, 0.0f, GEngine->GetSubtitleFont(), 1.0f);
	// Drawing Text Shadow (with a slight positional difference)
	DrawText(TEXT("David Xu - davidx@usc.edu"), FLinearColor::Black, 2.0f, 2.0f, GEngine->GetSubtitleFont(), 0.5f);
	// Drawing Actual Text
	DrawText(TEXT("David Xu - davidx@usc.edu"), FLinearColor::Green, 0.0f, 0.0f, GEngine->GetSubtitleFont(), 0.5f);

	// Checking for Best candidate and displaying Hint
	if (UInteractSubsystem* MyInteractSystem = GetWorld()->GetSubsystem<UInteractSubsystem>())
	{
		if (UInteractComponent* Component = MyInteractSystem->GetBestCandidate().Get())
		{
			if (AActor* CurrentTorch = Component->GetOwner())
			{
				FVector TorchLoc = CurrentTorch->GetActorLocation();
				FVector HintLoc = Project(TorchLoc);

				// Draw Interact
				// Use GetTextSize to center

				float TWidth = 0.0f, THeight = 0.0f;

				GetTextSize("[E] - Interact", TWidth, THeight, nullptr, 2.0f);
				FVector2D TextSize = FVector2D(TWidth, THeight);

				// Calculate the center position of the text
				FVector2D TextCenter = FVector2D(HintLoc.X - TextSize.X / 2, HintLoc.Y - TextSize.Y / 2);

				DrawText("[E] - Interact", FLinearColor::Red, TextCenter.X, TextCenter.Y, nullptr, 2.0f);
			}
		}
	}

	// Draw Health -> Also assuming single player
	// Using RoundToInt to display as integer
	/*if (ATopDownCharacter* MyCharacter = Cast<ATopDownCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		int PlayerHealth = FMath::RoundToInt(MyCharacter->CurrentHealth);
		DrawText(FString::Printf(TEXT("Health: %d"), PlayerHealth), FColor::Green, 0.0f, 50.0f, GEngine->GetSubtitleFont(), 0.5f);
	}*/

#if ENABLE_DRAW_DEBUG

	if (CVarDebugPuzzles.GetValueOnGameThread() != 0)
	{
		for (TObjectIterator<UPuzzleComponent> Itr; Itr; ++Itr)
		{
			Itr->DebugDrawOutput();
		}
	}
	

#endif
}
