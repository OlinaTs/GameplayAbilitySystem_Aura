// Copyright Mazi Studios


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	// we get the Forward Vector of the Summoner
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	// we get the Location of the Summoner
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	// this will be the angle between each of the Vectors that we want to Spawn the minions along
	const float DeltaSpread = SpawnSpread / NumMinions;

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2, FVector::UpVector);
	TArray<FVector> SpawnLocations;
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		const FVector ChosenSpawnLocation = Location + Direction * FMath::RandRange(MinSpawnDistance, MaxSpawnDistance);
		SpawnLocations.Add(ChosenSpawnLocation);
		
		DrawDebugSphere(GetWorld(), ChosenSpawnLocation, 10.f, 12, FColor::Cyan, false, 3.f);
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location, Location + Direction * MaxSpawnDistance, 4.f, FLinearColor::Red, 3.f);
		DrawDebugSphere(GetWorld(), Location + Direction * MinSpawnDistance, 5.f, 12, FColor::Black, false, 3.f);
		DrawDebugSphere(GetWorld(), Location + Direction * MaxSpawnDistance, 5.f, 12, FColor::Black, false, 3.f);
	}

	return SpawnLocations;
}
