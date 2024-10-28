// Copyright Mazi Studios

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Aura Gameplay Tags
 *
 * Singleton containing native Gameplay Tags
 */

struct FAuraGameplayTags
{
public:
    /* with a Singleton we create a static Getter function,
    * so we don't need an Instance of the class to exist to be able to call one of its static functions */
    static const FAuraGameplayTags& Get() {return GameplayTags;}
    static void InitializeNativeGameplayTags();

    FGameplayTag Attributes_Secondary_Armor;
 
protected:

private:
    static FAuraGameplayTags GameplayTags;
};