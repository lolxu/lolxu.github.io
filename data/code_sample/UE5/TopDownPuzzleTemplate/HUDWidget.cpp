// Copyright David Xu - davidx@usc.edu


#include "HUDWidget.h"

#include "TopDownCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Update stuff
	if (auto Char = Cast<ATopDownCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		const float HealthPercent = Char->GetHealthPercent();
		HealthBar->SetPercent(Char->GetHealthPercent());
		if (HealthPercent > 0.7f)
		{
			HealthBar->SetFillColorAndOpacity(DefaultHealthColor);
		}
		else if (HealthPercent > 0.3f)
		{
			HealthBar->SetFillColorAndOpacity(DangerHealthColor);
		}
		else
		{
			HealthBar->SetFillColorAndOpacity(CriticalHealthColor);
		}
		FString HealthAsString = FString::Printf(TEXT("%d"), static_cast<int>(Char->GetCurrentHealth()));
		HealthAmount->SetText(FText::FromString(HealthAsString));
	}
}
