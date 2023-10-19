// Copyright David Xu - davidx@usc.edu


#include "FireComponent.h"

#include "Kismet/GameplayStatics.h"

UFireComponent::UFireComponent()
{
	// prevent ticking 
	PrimaryComponentTick.bCanEverTick = false;
}

bool UFireComponent::GetFireStatus() const
{
	return IsOnFire;
}

void UFireComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UFireComponent::FHandleOnBeginOverlap);
	if (bStartOnFire)
	{
		NativeCatchFire(GetOwner(), true);
	}
}

void UFireComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	OnComponentBeginOverlap.RemoveAll(this);
}

void UFireComponent::NativeCatchFire(AActor* InputActor, bool bIncomingFire)
{
	IsOnFire = true;
	OnFire.Broadcast();

	UGameplayStatics::SpawnSoundAttached(UFireSound, this);
	UGameplayStatics::SpawnEmitterAttached(UFireParticles, this);
}

void UFireComponent::FHandleOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UFireComponent* OtherFireComp = OtherActor->FindComponentByClass<UFireComponent>())
	{
		if (!IsOnFire && OtherFireComp->GetFireStatus())
		{
			NativeCatchFire(GetOwner(), true);
		}
	}
}


