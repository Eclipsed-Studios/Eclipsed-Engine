#include "Settings.h"

#include "CoreEngine/TypeChecks.h"

namespace Eclipse
{
	template<typename T>
	inline T Settings::Get(const char* key)
	{
		return T();
	}

	template<typename T>
	inline void Settings::Set(const char* key, T& value)
	{
	}
}