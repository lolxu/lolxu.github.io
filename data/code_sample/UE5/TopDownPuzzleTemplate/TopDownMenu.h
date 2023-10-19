// Copyright David Xu - davidx@usc.edu

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TopDownMenu.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UTopDownMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UTopDownMenu(const FObjectInitializer& ObjectInitializer);
protected:
	//UUserWidget interface
	// Called when the widget is created in game (may happen multiple times)
	virtual void NativeConstruct() override;
	// Called when a key is pressed down
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);
	//~ End UUserWidget interface
	
	// Called when changing the selection index
	void SetSelectedIndex(int InSelectedIndex);
private:
	int SelectedIndex = 0;
	TArray<TWeakObjectPtr<class UTopDownButton>> Buttons;
};
