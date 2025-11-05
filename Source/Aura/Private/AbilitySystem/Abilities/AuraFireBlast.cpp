// Copyright Mazi Studios


#include "AbilitySystem/Abilities/AuraFireBlast.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"

FString UAuraFireBlast::GetDescription(int32 Level)
{
	int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	float ManaCost = FMath::Abs(GetManaCost(Level));
	float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
	// Title
	"<Title>FIRE BLAST</>\n\n"

	// Level
	"<Small>Level: </><Level>%d</>\n"

	// Mana Cost
	"<Small>Mana Cost: </><ManaCost>%.1f</>\n"

	// Cooldown
	"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

	// Number of Fireballs
	"<Default>Launches %d</>"
	"<Default> fire balls in all directions, each coming back and </>"
	"<Default>exploding upon return, causing </>"

	// Damage
	"<Damage>%d</><Default> radial fire damage with "
	"a chance to burn.</>"),

	// Values
	Level,
	ManaCost,
	Cooldown,
	NumFireBalls,
	ScaledDamage);
}

FString UAuraFireBlast::GetNextLevelDescription(int32 Level)
{
	int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	float ManaCost = FMath::Abs(GetManaCost(Level));
	float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
	// Title
	"<Title>NEXT LEVEL: </>\n\n"

	// Level
	"<Small>Level: </><Level>%d</>\n"

	// Mana Cost
	"<Small>Mana Cost: </><ManaCost>%.1f</>\n"

	// Cooldown
	"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

	// Number of Fireballs
	"<Default>Launches %d</>"
	"<Default> fire balls in all directions, each coming back and </>"
	"<Default>exploding upon return, causing </>"

	// Damage
	"<Damage>%d</><Default> radial fire damage with "
	"a chance to burn.</>"),

	// Values
	Level,
	ManaCost,
	Cooldown,
	NumFireBalls,
	ScaledDamage);
}

TArray<AAuraFireBall*> UAuraFireBlast::SpawnFireBalls()
{
	TArray<AAuraFireBall*> FireBalls;
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	TArray<FRotator> Rotators = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.f, NumFireBalls);

	for (const FRotator& Rotator : Rotators)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotator.Quaternion());
		
		AAuraFireBall* FireBall = GetWorld()->SpawnActorDeferred<AAuraFireBall>(
			FireBallClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			CurrentActorInfo->PlayerController->GetPawn(),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		FireBall->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->ReturnToActor = GetAvatarActorFromActorInfo();
		FireBall->ExplosionEffectParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->SetOwner(GetAvatarActorFromActorInfo());

		FireBalls.Add(FireBall);

		FireBall->FinishSpawning(SpawnTransform);
	}

	return FireBalls;
}

