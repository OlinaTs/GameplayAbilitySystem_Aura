// Copyright Mazi Studios


#include "Input/AuraInputConfig.h"

#include "GameplayTagsManager.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionforTag(FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FAuraInputAction& Action : AbilityInputActions)
	{
		// If the InputTag we gave it is equal with the InputTag of the Array,
		// then we return the Input Action 
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this))
	}

	return nullptr;
}
