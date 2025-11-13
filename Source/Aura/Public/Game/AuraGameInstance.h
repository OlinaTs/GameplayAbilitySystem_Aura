// Copyright Mazi Studios

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AuraGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	/* we set the PlayerStartTag, LoadSlotName and LoadSlotIndex
     * in the MVVM_LoadScreen inside NewSlotButtonPressed() */
	UPROPERTY()
	FName PlayerStartTag = FName();
	
	UPROPERTY()
	FString LoadSlotName;

	UPROPERTY()
	int32 LoadSlotIndex;
};
