// Copyright Mazi Studios


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"


UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
    if(bIsLocallyControlled)
    {
	    SendMouseCursorDate();
    }
	else
	{
		// TODO: We're on the Server, so listen for target data
	}
	

}

void UTargetDataUnderMouse::SendMouseCursorDate()
{
	// everything within this scope should be predicted. Server allows us to do what we do locally,
	// and the server will do it when the server knows about it
	FScopedPredictionWindow PredictionWindow(AbilitySystemComponent.Get());
	
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	// we create a DataHandle, so we can use it in the ServerSetReplicatedTargetData()
    FGameplayAbilityTargetDataHandle DataHandle;
	// we create a new Object of type FGameplayAbilityTargetData_SingleTargetHit
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
    DataHandle.Add(Data);
	
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
