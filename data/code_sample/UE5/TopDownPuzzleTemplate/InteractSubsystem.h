// Copyright David Xu - davidx@usc.edu

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "InteractSubsystem.generated.h"

/**
 *
 */
UCLASS()
class TOPDOWN_API UInteractSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	// For initializing and deinitializing sub systems
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void AddComponent(class UInteractComponent* Component);
	void RemoveComponent(class UInteractComponent* Component);
	void PerformInteract();

	virtual void	Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;

	TWeakObjectPtr<class UInteractComponent> GetBestCandidate();

protected:
	virtual bool DoesSupportWorldType(EWorldType::Type WorldType) const override;

	TArray<TWeakObjectPtr<class UInteractComponent>> InteractComponents;
	TWeakObjectPtr<class UInteractComponent>		 BestCandidate;

	float InteractDistance = 200.0f;
	float InteractAngle = 135.0f;
};
