// Copyright Mazi Studios


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for(const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if(Info.AttributeTag == AttributeTag)
		{
			return Info;
		}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for Attribute Tag [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FAuraAttributeInfo();
}
