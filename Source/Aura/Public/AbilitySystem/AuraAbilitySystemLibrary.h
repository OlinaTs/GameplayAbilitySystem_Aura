// Copyright Mazi Studios

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAbilitySystemComponent;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObjext);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObjext);

	/* this function will Initialize Default Attributes based on a Character Class and the Level */
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySstemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes (const UObject* WorldContextObjext, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);
};
