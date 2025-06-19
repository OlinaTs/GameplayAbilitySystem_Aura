// Copyright Mazi Studios


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP) const
{
	int32 Level = 1;
	bool bSearching = true;

	while (bSearching)
	{
		// LevelUpInformation[1] = Level 1 Information
		// LevelUpInformation[2] = Level 2 Information 
		if (LevelUpInformation.Num() - 1 <= Level) return Level;

		// If the XP is bigger or equal with the LevelUpRequirement of our current Level
		if (XP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			// then we add one more Level
			++Level;
		}
		else
			// If the XP is NOT bigger or equal with the LevelUpRequirement of our current Level
		{
			// then we just return our current Level
			bSearching = false;
		}
	}
	return Level;
}
