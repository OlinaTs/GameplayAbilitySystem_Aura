// Copyright Mazi Studios

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraInputConfig.generated.h"


/* to create a link between Input Actions and GameplayTags
 * we first create a struct with an InputAction and a GameplayTag */
USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};


/**
 * 
 */
UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:

	/* this will return the Input Action associated with a given Tag */
	const UInputAction* FindAbilityInputActionforTag(FGameplayTag& InputTag, bool bLogNotFound = false) const;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraInputAction> AbilityInputActions;
};
