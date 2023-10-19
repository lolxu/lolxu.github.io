// Copyright David Xu - davidx@usc.edu

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "FireComponent.generated.h"

/**
 * Fire Component
 */

// Setting delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireDelegate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOPDOWN_API UFireComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	// Constructor for the component
	UFireComponent();

	// Getter for IsOnFire
	bool GetFireStatus() const;
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void NativeCatchFire(AActor* InputActor, bool bIncomingFire);

	bool IsOnFire = false;

	// Fire Particles to play
	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> UFireParticles;

	// Fire sound to play
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> UFireSound;

	// The delegate for catches on fire
	UPROPERTY(BlueprintAssignable)
	FOnFireDelegate OnFire;

	// Should this object start with fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bStartOnFire = false;
	
	UFUNCTION()
	void FHandleOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
