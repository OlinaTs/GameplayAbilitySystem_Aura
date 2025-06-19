// Copyright Mazi Studios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class ULevelUpInfo;

/* whenever one of our Stats change, we'll broadcast that to whoever binds to our Delegate.  */
/* with MULTICAST Delegates we don't need to have a Param name after the variable type */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChange, int32 /* StatValue */)

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AAuraPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/* this is a Getter for the Ability System Component */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/* this is a Getter for the Attribute Set */
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;
	
	FOnPlayerStatChange OnXPChangedDelegate;
	FOnPlayerStatChange OnLevelChangedDelegate;

	/* Getters */
    FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	FORCEINLINE int32 GetXP() const { return XP; }

	/* AddTo */
	void AddToXP(int32 InXP);
	void AddToLevel(int32 InLevel);

	/* Setters */
	void SetXP(int32 InXP);
	void SetLevel(int32 InLevel);

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;

	UFUNCTION()
    void OnRep_Level(int32 OldLevel);

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_XP)
	int32 XP = 1;

	UFUNCTION()
	void OnRep_XP(int32 OldXP);


};
