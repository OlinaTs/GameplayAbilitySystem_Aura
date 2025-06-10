// Copyright Mazi Studios


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());

	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	// whenever the Health changes,the function void HealthChanged(const FOnAttributeChangeData& Data) will be called
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
	   [this](const FOnAttributeChangeData& Data)
	   {
	   	   OnHealthChanged.Broadcast(Data.NewValue);
	   }
    );

	// whenever the MaxHealth changes,the function void MaxHealthChanged(const FOnAttributeChangeData& Data) will be called
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
	    [this](const FOnAttributeChangeData& Data)
	    {
	    	OnMaxHealthChanged.Broadcast(Data.NewValue);
	    }
    );
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
	    [this](const FOnAttributeChangeData& Data)
	    {
	    	OnManaChanged.Broadcast(Data.NewValue);
	    }
    );

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
	    {
			OnMaxManaChanged.Broadcast(Data.NewValue);
	    }
	);

	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (AuraASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(AuraASC);
		}
		else
		{
			AuraASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		}
		
		AuraASC->EffectAssetTags.AddLambda(
			 [this](const FGameplayTagContainer& AssetTags)
			 {
				 for(const FGameplayTag& Tag : AssetTags)
				 {
					 // For example, say that Tag = Message.HealthPotion
					 // "Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
					 FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
					 if (Tag.MatchesTag(MessageTag))
					 {
						 const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						 MessageWidgetRowDelegate.Broadcast(*Row);
					 }
				 }
			 }   
		);
	}
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UAuraAbilitySystemComponent* AuraAbilitySystemXComponent)
{
	// TODO: Get information about all given Abilities, lookup their Ability Info, and broadcast it to Widgets
	if (!AuraAbilitySystemXComponent->bStartupAbilitiesGiven) return;

	
}
