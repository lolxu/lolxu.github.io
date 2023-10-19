// Copyright David Xu - davidx@usc.edu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TopDownHUD.generated.h"

/**
 *
 */
UCLASS()
class TOPDOWN_API ATopDownHUD : public AHUD
{
	GENERATED_BODY()

	// Copied from HUD.h, used override
	virtual void DrawHUD() override;
};
