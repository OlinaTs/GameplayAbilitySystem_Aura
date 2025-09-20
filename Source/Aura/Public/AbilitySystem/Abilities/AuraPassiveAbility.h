// Copyright Mazi Studios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraPassiveAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraPassiveAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	// this is the Callback function that we want to buy to the DeactivatePassiveAbility delegate
	// that we've declared in the AbilitySystemComponent and will be Broadcasted in the AbilitySystemComponent
	void ReceiveDeactivate(const FGameplayTag& AbilityTag);
};
