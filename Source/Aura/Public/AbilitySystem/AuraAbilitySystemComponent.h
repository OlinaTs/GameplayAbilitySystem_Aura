// Copyright Mazi Studios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

class ULoadScreenSaveGame;
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /* AssetTags */);
// this can be broadcast when the Abilities are given
DECLARE_MULTICAST_DELEGATE(FAbilitiesGiven);
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FAbilityStatusChanged, const FGameplayTag& /*AbilityTag*/, const FGameplayTag& /*StatusTag*/, int32 /*AbilityLevel*/);
DECLARE_MULTICAST_DELEGATE_FourParams(FAbilityEquipped, const FGameplayTag& /*AbilityTag*/, const FGameplayTag& /*StatusTag*/, const FGameplayTag& /*Slot*/, const FGameplayTag& /*PreviousTag*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FDeactivatePassiveAbility, const FGameplayTag& /*AbilityTag*/)
DECLARE_MULTICAST_DELEGATE_TwoParams(FActivatePassiveEffect, const FGameplayTag& /*AbilityTag*/, bool /*bActivate*/)
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	/* when this function is called, we know the Ability Actor Info has been set */
	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;
	FAbilitiesGiven AbilitiesGivenDelegate;
	FAbilityStatusChanged AbilityStatusChanged;
	FAbilityEquipped AbilityEquipped;
	FDeactivatePassiveAbility DeactivatePassiveAbility;
	FActivatePassiveEffect ActivatePassiveEffect;

	void AddCharacterAbilitiesFromSaveData(ULoadScreenSaveGame* SaveData);
	/* we want to grant the Abilities */
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities);
	
	bool bStartupAbilitiesGiven = false;
	
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	
	void ForEachAbility(const FForEachAbility& Delegate);

	/* Insert the AbilitySpec, and we'll find its AbilityTag */
	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	
	/* Insert the AbilitySpec, and we'll find its InputTag */
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	
	/* Insert the AbilitySpec, and we'll find its Ability Status */
	static FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	
	/* Insert the Ability Tag, and we'll find its Status Tag */
	FGameplayTag GetStatusFromAbilityTag(const FGameplayTag& AbilityTag);
	
	/* Insert the Ability Tag, and we'll find its Slot aka Input Tag */
	FGameplayTag GetSlotFromAbilityTag(const FGameplayTag& AbilityTag);
	
	/* SlotIsEmpty(Slot) = we want to see if the SpellGlobe down in the Equipped Row
	 * that we're clicking is Empty or not */
	bool SlotIsEmpty(const FGameplayTag& Slot);
	
	/* This function just checks whether the given ability (Spec) has the Slot(InputTag) */
	static bool AbilityHasSlot(const FGameplayAbilitySpec& Spec, const FGameplayTag& Slot);

	static bool AbilityHasAnySlot(const FGameplayAbilitySpec& Spec);

	/* returns whatever AbilitySpec is associated with a given slot */
	FGameplayAbilitySpec* GetSpecWithSLot(const FGameplayTag& Slot);

	bool IsPassiveAbility(const FGameplayAbilitySpec& Spec) const;

	/* assign the new Slot/InputTag to the Ability */
	static void AssignSlotToAbility(FGameplayAbilitySpec& Spec, const FGameplayTag& Slot);

	/* Broadcasts the ActivatePassiveEffect delegate */
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastActivatePassiveEffect(const FGameplayTag& AbilityTag, bool bActivate);
	
	/* Insert the Ability tag and, if this AbilitySystemComponent has that Ability
	 * with that Tag, we'll return a pointer to an AbilitySpec
	 * otherwise we'll return a nullptr */
	FGameplayAbilitySpec* GetSpecFromAbilityTag(const FGameplayTag& AbilityTag);
	
	
	void UpgradeAttribute(const FGameplayTag& AttributeTag);

	UFUNCTION(Server, Reliable)
	void ServerUpgradeAttribute(const FGameplayTag& AttributeTag);

	void UpdateAbilityStatuses(int32 Level);

	UFUNCTION(Server, Reliable)
	void ServerSpendSpellPoints(const FGameplayTag& AbilityTag);

	/* Slot = the InputTag of the SpellGlobe in the EquippedSpellRow we just pressed */
	UFUNCTION(Server, Reliable)
	void ServerEquipAbility(const FGameplayTag& AbilityTag, const FGameplayTag& Slot);

	UFUNCTION(Client, Reliable)
	void ClientEquipAbility(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreviousSlot);

	bool GetDescriptionsByAbilityTag(const FGameplayTag& AbilityTag, FString& OutDescription, FString& OutNextLevelDescription);

	// we clear the Input Tag from the Slot
	static void ClearSlot(FGameplayAbilitySpec* Spec);
	// clear any Abilities we have of a Given SLot
	void ClearAbilitiesOfSlot(const FGameplayTag& Slot);
	static bool AbilityHasSlot(FGameplayAbilitySpec* Spec, const FGameplayTag& Slot);
protected:

	virtual void OnRep_ActivateAbilities() override;
	
	/* WE CREATE THE void EffectApplied() from the following
	 * 'Delegate for when an effect is applied'
	 * DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnGameplayEffectAppliedDelegate,
	 * UAbilitySystemComponent*, const FGameplayEffectSpec&, FActiveGameplayEffectHandle); */
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

	UFUNCTION(Client, Reliable)
	void ClientUpdateAbilityStatus(const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 AbilityLevel);
};
