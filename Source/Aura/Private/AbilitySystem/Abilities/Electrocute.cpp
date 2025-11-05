// Copyright Mazi Studios


#include "AbilitySystem/Abilities/Electrocute.h"

FString UElectrocute::GetDescription(int32 Level)
{
	int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	float ManaCost = FMath::Abs(GetManaCost(Level));
	float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>ELECTROCUTE</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"

			// Mana Cost
			"<Small>Mana Cost: </><ManaCost>%.1f</>\n"

			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			
			"<Default>Emits a beam of Lightning, "
			"connecting with the Target, repeatedly causing </>"

			// Damage
			"<Damage>%d</><Default>lightning damage with "
			"a chance to stun.</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
		// Title
		"<Title>ELECTROCUTE</>\n\n"

		// Level
		"<Small>Level: </><Level>%d</>\n"

		// Mana Cost
		"<Small>Mana Cost: </><ManaCost>%.1f</>\n"

		// Cooldown
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		// Additional Number of Shock Targets
		"<Default>Emits a beam of lightning, "
		"propagating to %d additional targets nearby, causing </>"

		// Damage
		"<Damage>%d</><Default>lightning damage with "
		"a chance to stun.</>"),

		// Values
		Level,
		ManaCost,
		Cooldown,
		// MaxNumShockTargets - 1 because we already have our first beam and these are the additional Targets
		FMath::Min(Level, MaxNumShockTargets - 1),
		ScaledDamage);
	}
}

FString UElectrocute::GetNextLevelDescription(int32 Level)
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

		// Additional Number of Shock Targets
		"<Default>Emits a beam of lightning, "
		"propagating to %d additional targets nearby, causing </>"

		// Damage
		"<Damage>%d</><Default> lightning damage with "
		"a chance to stun.</>"),

		// Values
		Level,
		ManaCost,
		Cooldown,
		// MaxNumShockTargets - 1 because we already have our first beam and these are the additional Targets
		FMath::Min(Level, MaxNumShockTargets - 1),
		ScaledDamage);
}
