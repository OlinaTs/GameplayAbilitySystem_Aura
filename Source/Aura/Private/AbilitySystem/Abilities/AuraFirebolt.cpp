// Copyright Mazi Studios


#include "AbilitySystem/Abilities/AuraFirebolt.h"

#include "AuraGameplayTags.h"

FString UAuraFirebolt::GetDescription(int32 Level)
{
	int32 Damage = GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire);
	float ManaCost = FMath::Abs(GetManaCost(Level));
	float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"

			// Mana Cost
			"<Small> Mana Cost: </><ManaCost>%.1f</>\n"

			// Cooldown
			"<Small> Cooldown: </><Cooldown>%.1f</>\n\n"
			
			"<Default>Launches a bolt of fire, "
			"exploding on impact and dealing: </>"

			// Damage
			"<Damage>%d</> <Default> fire damage with "
			"a chance to burn.</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			Damage);
	}
	else
	{
		return FString::Printf(TEXT(
		// Title
		"<Title>FIRE BOLT</>\n\n"

		// Level
		"<Small>Level: </><Level>%d</>\n"

		// Mana Cost
		"<Small> Mana Cost: </><ManaCost>%.1f</>\n"

		// Cooldown
		"<Small> Cooldown: </><Cooldown>%.1f</>\n\n"

		// Number of Firebolts
		"<Default>Launches %d bolts of fire, "
		"exploding on impact and dealing: </>"

		// Damage
		"<Damage>%d</> <Default> fire damage with "
		"a chance to burn.</>"),

		// Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumProjectiles),
		Damage);
	}
}

FString UAuraFirebolt::GetNextLevelDescription(int32 Level)
{
	int32 Damage = GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire);
	float ManaCost = FMath::Abs(GetManaCost(Level));
	float Cooldown = GetCooldown(Level);
	
	return FString::Printf(TEXT(
		// Title
		"<Title>NEXT LEVEL</>\n\n"

		// Level
		"<Small>Level: </><Level>%d</>\n"

		// Mana Cost
		"<Small> Mana Cost: </><ManaCost>%.1f</>\n"

		// Cooldown
		"<Small> Cooldown: </><Cooldown>%.1f</>\n\n"

		// Number of Firebolts
		"<Default>Launches %d bolts of fire, "
		"exploding on impact and dealing: </>"

		// Damage
		"<Damage>%d</> <Default> fire damage with "
		"a chance to burn.</>"),

		// Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumProjectiles),
		Damage);
}
