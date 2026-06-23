#include "ReflectionType.h"

#include <cstring>

const Property* ClassInfoBase::GetProperty(const char* propertyName) const
{
	for (size_t i = 0; i < GetPropertyCount(); i++)
	{
		const Property* prop = GetProperties()[i];
		if (!strcmp(prop->name, propertyName))
			return prop;
	}

	return nullptr;
}
