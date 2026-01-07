#include "Settings.h"

#include "CoreEngine/TypeChecks.h"

namespace Eclipse
{
	template<typename T>
	inline T HejsanKOmis::Get(const char* key)
	{
		return T();
	}

	template<typename T>
	inline void HejsanKOmis::Set(const char* key, T& value)
	{
	}
}