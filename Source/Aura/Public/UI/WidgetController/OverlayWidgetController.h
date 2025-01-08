// Copyright Mazi Studios

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	/* when we display Text to the user in the form of a Widget, we use FText */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	/* for any given Gameplay Tag, there will be a Widget that we can create
	 * and add to the Viewport whenever we receive this Tag
	 * in the form of a Gameplay Effect */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

class UAuraUserWidget;

/** We declare a delegate that can broadcast a float */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:
	/** we call it in the AuraHUD in the InitOverlay() */
	virtual void BroadcastInitialValues() override;
	
	/** we call it in the AuraHUD in the GetOverlayWidgetController() */
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	/* it's going to find the row and return the row, no matter its type */
	template<typename T>
	T* GetDataTableRowbyTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowbyTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	/* we're finding the DataTable Row by TagName because, in the Engine, we used the Tag Name as our Row name,
	 * so we get the TagName = Tag.GetTagName() to find the row */
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}