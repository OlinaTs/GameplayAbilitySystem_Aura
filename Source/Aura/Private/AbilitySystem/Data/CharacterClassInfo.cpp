// Copyright Mazi Studios


#include "AbilitySystem/Data/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass)
{
	// returns the Information given a Character Class Enum constant
	return CharacterClassInformation.FindChecked(CharacterClass);
}
