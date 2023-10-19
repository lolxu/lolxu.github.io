// Copyright David Xu - davidx@usc.edu


#include "AnimNotifyState_Invulnerable.h"

#include "TopDownCharacter.h"

void UAnimNotifyState_Invulnerable::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	if (ATopDownCharacter* MyCharacter = Cast<ATopDownCharacter>(MeshComp->GetOwner()))
	{
		MyCharacter->AddInvulnerableRequestor(this);
		MyCharacter->BodyColorTurnBlue();
	}
}

void UAnimNotifyState_Invulnerable::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ATopDownCharacter* MyCharacter = Cast<ATopDownCharacter>(MeshComp->GetOwner()))
	{
		MyCharacter->RemoveInvulnerableRequestor(this);
		MyCharacter->BodyColorTurnNormal();
	}
}
