// Copyright Mazi Studios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChangedSignature, int32, NewValue);
// We create a Delegate that can Broadcast Ability Info
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityInfoSignature, const FAuraAbilityInfo&, Info);

class UAttributeSet;
class UAbilitySystemComponent;
class UAuraAttributeSet;
class AAuraPlayerState;
class AAuraPlayerController;
class UAbilityInfo;

/* a struct where it can receive the following key variables when we create one */
USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	
	FWidgetControllerParams() {}

	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};


/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(FWidgetControllerParams& WCParams);

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();

	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FAbilityInfoSignature AbilityInfoDelegate;

	void BroadcastAbilityInfo();
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<UAbilityInfo> AbilityInfo;
	
	/* The Widget Controller will receive the data from these variables to broadcast to our UserWidgets */
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController");
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController");
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController");
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController");
	TObjectPtr<UAttributeSet> AttributeSet;
	/* end - The Widget Controller will receive the data from these variables to broadcast to our UserWidgets */

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController");
	TObjectPtr<AAuraPlayerController> AuraPlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController");
	TObjectPtr<AAuraPlayerState> AuraPlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController");
	TObjectPtr<UAuraAbilitySystemComponent> AurabilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController");
	TObjectPtr<UAuraAttributeSet> AuraAttributeSet;

	AAuraPlayerController* GetAuraPC();
	AAuraPlayerState* GetAuraPS();
	UAuraAbilitySystemComponent* GetAuraASC();
	UAuraAttributeSet* GetAuraAS();
};
