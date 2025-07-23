
// Copyright Mazi Studios


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/SpellMenuWidgetController.h"


// a GETTER where if OverlayWidgetController isn't constructed yet, we create one
// and if it has, it won't be null and we return it
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		// we create a new OverlayWidgetController
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

// a GETTER where if AttributeMenuWidgetController isn't constructed yet, we create one
// and if it has, it won't be null and we return it
UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		// we create a new AttributeMenuWidgetController
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

// a GETTER where if SpellMenuWidgetController isn't constructed yet, we create one
// and if it has, it won't be null and we return it
USpellMenuWidgetController* AAuraHUD::GetSpellMenuWidgetController(FWidgetControllerParams& WCParams)
{
	if (SpellMenuWidgetController == nullptr)
	{
		SpellMenuWidgetController = NewObject<USpellMenuWidgetController>(this, SpellMenuWidgetControllerClass);
		SpellMenuWidgetController->SetWidgetControllerParams(WCParams);
		SpellMenuWidgetController->BindCallbacksToDependencies();
	}
	return SpellMenuWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWIdgetClass uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWIdgetControllerClass uninitialized, please fill out BP_AuraHUD"));

	// a) we construct the OverlayWidget
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	// b) we construct the WidgetController
	FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	// c) we set the OverlayWidget to have the WidgetController as its controller
	OverlayWidget->SetWidgetController(WidgetController);

	WidgetController->BroadcastInitialValues();
	
	// d) we add the widget to the Viewport
	Widget->AddToViewport();
}

