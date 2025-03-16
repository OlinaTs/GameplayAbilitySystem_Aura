// Copyright Mazi Studios


#include "AI/BTService_FindNearestPlayer.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, *AIOwner->GetName());
	GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, *ActorOwner->GetName());

	APawn* OwningPawn = AIOwner->GetPawn();

	// if the owner of this BTService is an Enemy, then the TargetTag will be the Player
	const FName TargetTag = OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");

	// GetAllActorsWithTag will fill all the ActorsWithTag array with all the Actors in the world
	// who have the Player Tag
	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(OwningPawn, TargetTag, ActorsWithTag);
}
