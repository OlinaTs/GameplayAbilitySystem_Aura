// Copyright Mazi Studios


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/AuraUserWidget.h"
#include "AuraGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("Health Bar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AAuraEnemy::HighlightActor()
{
	// Highlighting
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighlightActor()
{
	// Unhighligting
	GetMesh()->SetRenderCustomDepth(false);
	
	Weapon->SetRenderCustomDepth(false);
}

int32 AAuraEnemy::GetPlayerLevel()
{
	return Level;
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;

	// 1. we set the Health's Bar Widget Controller inside the Enemy,
	// amd the Enemy owns it
	if (UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		AuraUserWidget->SetWidgetController(this);
	}

	// 2. we're broadcasting Delegates for when the Health and Max Health of the Enemy changes
	if (const UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda(
		    [this] (const FOnAttributeChangeData& Data)
		    {
			    OnHealthChanged.Broadcast(Data.NewValue);
		    }
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda(
		[this] (const FOnAttributeChangeData& Data)
		   {
			    OnMaxHealthChanged.Broadcast(Data.NewValue);
		   }
	    );

		// whenever our Enemy AbilitySystemComponent receives the Effects.HitReactTag,
		// the function HitReactChanged will be called
		AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
		   this,
		   &AAuraEnemy::HitReactTagChanged
		);
		
		// 3. we're broadcasting the Initial values 
		OnHealthChanged.Broadcast(AuraAS->GetHealth());
		OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
	}
}

void AAuraEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	// if the Enemy is hit by someone, thus is bHitReacting, then the walk speed will be zero
	// if not then it'll return to his BaseWalkSpeed
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

void AAuraEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}

void AAuraEnemy::InitializeDefaultAttributes() const
{
	UAuraAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
