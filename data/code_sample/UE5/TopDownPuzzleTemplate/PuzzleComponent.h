// Copyright David Xu - davidx@usc.edu

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzleComponent.generated.h"

// Setting Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPuzzleComponentOnReceiveInput, class AActor*, InputActor, bool, bValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPuzzleComponentOnPuzzleReset);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOPDOWN_API UPuzzleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPuzzleComponent();

	// Track whether or not the output is active
	UPROPERTY(Transient, BlueprintReadOnly)
	bool bIsOutputActive = false;

	// Track which actor this puzzle component should send the output to
	UPROPERTY(EditInstanceOnly)
	TSoftObjectPtr<AActor> OutputActor;

	// Asign for receiving puzzle inputs
	UPROPERTY(BlueprintAssignable)
	FPuzzleComponentOnReceiveInput OnReceiveInput;

	// Asign for puzzle resets
	UPROPERTY(BlueprintAssignable)
	FPuzzleComponentOnPuzzleReset OnPuzzleReset;

	// Resets puzzle
	UFUNCTION(BlueprintCallable)

	virtual void PuzzleReset();

	/**
	 * Specify whether or not the output of this puzzle component should be active
	 * @param bActive The boolean value to set the IsOutputActive variable
	 */
	UFUNCTION(BlueprintCallable)
	virtual void SetOutputActive(bool bActive);

	/**
	 * Specify which output actor is currently active in the puzzle rotation
	 * @param the output actor that is active right now
	 */
	UFUNCTION(BlueprintCallable)
	void ChangeOutputActor(AActor* MyActor);

	// Debug draw
	void DebugDrawOutput();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void NativeReceiveInput(AActor* InputActor, bool bIncomingValue);

private:
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
