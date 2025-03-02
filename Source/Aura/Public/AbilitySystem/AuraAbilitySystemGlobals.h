// Copyright Mazi Studios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "AuraAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

	/* creates a new FGameplayEffectContext of our custom type-> FAuraGameplayEffectContext */
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
