// Copyright Mazi Studios

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAuraAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

protected:
	/** The Widget Controller will receive the data from these variables to broadcast to our UserWidgets */
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController");
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController");
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController");
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController");
	TObjectPtr<UAttributeSet> AttributeSet;
	/** end - The Widget Controller will receive the data from these variables to broadcast to our UserWidgets */
};
