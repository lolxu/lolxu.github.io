// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownCharacter.generated.h"

UCLASS(Blueprintable)
class ATopDownCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATopDownCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	// Override begin play
	virtual void BeginPlay() override;

	// Override can crouch for crouching
	virtual bool CanCrouch() const override;

	virtual bool ShouldTakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const override;

	// Override function for Actor take damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator, AActor * DamageCauser) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// This function should be called when you enter a blue trigger.
	// This will turn the player blue.
	UFUNCTION(BlueprintCallable)
	void OnEnterBlueTrigger();

	// This function should be called when you exit a blue trigger.
	// This will turn the player back to the original color when there are no more active volumes.
	UFUNCTION(BlueprintCallable)
	void OnExitBlueTrigger();

	// The blue character color when in a blue volume
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor BlueColor = FLinearColor::Blue;

	// The default character color when outside volumes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor DefaultColor = FLinearColor::White;

	// The montage for dash
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> DashMontage;

	// The montage for death
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> DeathMontage;

	// Function for starting dash
	void StartDash();

	// Bool for checking dashing or not
	UPROPERTY(Transient, BlueprintReadOnly)
	bool bIsDashing;

	// Get IsDashing bool
	bool GetIsDashing();

	// The dash movement multiplier
	UPROPERTY(EditAnywhere)
	float DashSpeedMultiplier = 2.0f;

	// The dash movement accelerator multiplier
	UPROPERTY(EditAnywhere)
	float DashAccelMultiplier = 5.0f;

	// The maximum health of player character
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.0f;

	// The current health of player character
	UPROPERTY(Transient, BlueprintReadOnly)
	float CurrentHealth;

	// Bool for checking is dead or not
	UPROPERTY(Transient, BlueprintReadOnly)
	bool bIsDead = false;

	// Add or remove the requestors
	void AddInvulnerableRequestor(UObject* Object);
	void RemoveInvulnerableRequestor(UObject* Object);

	void BodyColorTurnBlue();
	void BodyColorTurnNormal();

	float GetCurrentHealth() const {return CurrentHealth;}
	float GetHealthPercent() const {return CurrentHealth / MaxHealth;}
	
private:

	void EndDash();

	void DeactivateSkeletalMesh();
	
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// The parameter name for the body color
	UPROPERTY(EditDefaultsOnly)
	FName BodyColorParamName = FName(TEXT("Tint"));

	// Objects that could request invulnerability
	UPROPERTY(Transient)
	TArray<TWeakObjectPtr<UObject>> InvulnerableRequestors;

	int NumBlueVolumes = 0;
	float DashMontageLength = 0.0f;
	float DeathMontageLength = 0.0f;
	bool bHasDied = false;
	
	// Handle to manage the dash montage timer
	FTimerHandle DashTimerHandle;

	// Handle to manage the death montage timer
	FTimerHandle DeathTimerHandle;
};
